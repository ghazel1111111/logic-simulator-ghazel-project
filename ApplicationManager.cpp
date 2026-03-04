#include "ApplicationManager.h"

// Include all action headers
#include "Actions/AddANDgate2.h"
#include "Actions/AddANDgate3.h"
#include "Actions/AddNANDgate2.h"
#include "Actions/AddNORgate2.h"
#include "Actions/AddNORgate3.h"
#include "Actions/AddORgate2.h"
#include "Actions/AddXORgate2.h"
#include "Actions/AddXORgate3.h"
#include "Actions/AddXNORgate2.h"
#include "Actions/AddNOTgate.h"
#include "Actions/Addbuffergate.h"
#include "Actions/AddLEDgate.h"
#include "Actions/AddSwitchgate.h"
#include "Actions/AddConnection.h"
#include "AddLabelAction.h"
#include "copy.h" 
#include "Actions/Delete.h"
#include "SelectAction.h"
#include "Actions/MultiSelectAction.h" // ensure multi-select action is available
#include "MoveAction.h" // include MoveAction
#include "CutAction.h"
#include "EditLabelAction.h"
#include "Actions/SaveAction.h"
#include "Actions/LoadAction.h"
#include "Actions/ValidateAction.h"
#include "Actions/AddProbing.h"
#include "Actions/TruthTableAction.h"
#include "Components/Switch.h"
#include "Components/LED.h"
#include "Components/Gate.h"
#include "Components/Connection.h"
#include <fstream>
// Need Switch type for simulation toggle handling



ApplicationManager::ApplicationManager()
    : CompCount(0)
    , selectedComponent(nullptr)
    , InputInterface(nullptr)
    , OutputInterface(nullptr)
    , isSelectMode(false) // <<< IMPORTANT FIX
{
    // Initialize component pointers to avoid uninitialized-member warnings and ensure safe cleanup
    for (int i = 0; i < MaxCompCount; ++i)
        CompList[i] = nullptr;

    OutputInterface = new Output();
    InputInterface = OutputInterface->CreateInput();
}

ApplicationManager::~ApplicationManager()
{
    for (int i = 0; i < CompCount; i++)
        delete CompList[i];

    delete OutputInterface;
    delete InputInterface;
}

////////////////////////////////////////////////////////////////////
// Adding components
void ApplicationManager::AddComponent(Component* pComp)
{
    if (CompCount >= MaxCompCount)
        return;
    GraphicsInfo g = pComp->GetGraphicsInfo();

    if (g.y1 < UI.ToolBarHeight || g.y2 > UI.height - UI.StatusBarHeight)
    {
        if (OutputInterface)
            OutputInterface->PrintMsg("Error: place component inside the drawing area.");
        delete pComp;
        return;
    }

    CompList[CompCount++] = pComp;
}

////////////////////////////////////////////////////////////////////
// Get user action
ActionType ApplicationManager::GetUserAction()
{
    return InputInterface->GetUserAction();
}
void ApplicationManager::SetClipboard(Component* comps[], int count)
{
    clipboardCount = count;
    for (int i = 0; i < count && i < 200; ++i)
        clipboard[i] = comps[i];
}

int ApplicationManager::GetClipboard(Component* outComps[]) const
{
    for (int i = 0; i < clipboardCount; ++i)
        outComps[i] = clipboard[i];
    return clipboardCount;
}

void ApplicationManager::RemoveComponent(Component* c)
{
    for (int i = 0; i < CompCount; i++)
    {
        if (CompList[i] == c)
        {
            delete CompList[i];
            for (int j = i; j < CompCount - 1; j++)
                CompList[j] = CompList[j + 1];
            CompList[CompCount - 1] = nullptr;
            CompCount--;
            return;
        }
    }
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{

    Action* pAct = nullptr;

    switch (ActType)
    {

    case Add_probing:
        pAct = new AddProbing(this);
        break;


    case SAVE:
        pAct = new SaveAction(this);
        break;

    case LOAD:
        pAct = new LoadAction(this);
        break;

        // Gate actions
    case DEL:
        pAct = new Delete(this);
        break;
    case CUT:
        pAct = new CutAction(this);
        break;
    case Create_TruthTable:
        pAct = new TruthTableAction(this);
        break;
    case ADD_AND_GATE_2:     pAct = new AddANDgate2(this); break;
    case ADD_AND_GATE_3:     pAct = new AddANDgate3(this); break;
    case ADD_NAND_GATE_2:    pAct = new AddNANDgate2(this); break;
    case ADD_NOR_GATE_2:     pAct = new AddNORgate2(this); break;
    case ADD_NOR_GATE_3:     pAct = new AddNORgate3(this); break;
    case ADD_OR_GATE_2:      pAct = new AddORgate2(this); break;
    case ADD_XOR_GATE_2:     pAct = new AddXORgate2(this); break;
    case ADD_XOR_GATE_3:     pAct = new AddXORgate3(this); break;
    case ADD_XNOR_GATE_2:    pAct = new AddXNORgate2(this); break;
    case ADD_INV:            pAct = new AddNOTgate(this); break;
    case ADD_Buff:           pAct = new Addbuffergate(this); break;
    case ADD_LED:            pAct = new AddLEDgate(this); break;
    case ADD_Switch:         pAct = new AddSwitchgate(this); break;
    case ADD_CONNECTION:     pAct = new AddConnection(this); break;
    case COPY:               pAct = new CopyAction(this); break; // <-- added
    case MOVE:               pAct = new MoveAction(this); break; // handle MOVE action
    case ADD_Label:          pAct = new AddLabelAction(this); break;
    case Add_vildation:      pAct = new ValidateAction(this); break; //done
        // Select mode action (single)
    case SELECT:
        OutputInterface->PrintMsg("Select Mode: Click a component to select.");
        isSelectMode = true;
        pAct = new SelectAction(this);
        break;
    case EDIT_Label:          pAct = new EditLabelAction(this); break;
        // Multi-select mode — toggles components until user clicks empty area
    case MULTI_SELECT:
        pAct = new MultiSelectAction(this);
        break;

    // Simulation: toggle a switch under cursor and propagate signals
    case Add_operation:
    {
        int x = 0, y = 0;

        // Prompt the user to click a switch
        if (OutputInterface)
            OutputInterface->PrintMsg("Simulation: click on a switch to toggle it.");

        // Wait for the user's click
        InputInterface->GetPointClicked(x, y);

      
        if (OutputInterface)
            OutputInterface->ClearStatusBar();

        Component* clickedComp = GetComponentAt(x, y);
        if (!clickedComp)
        {
            if (OutputInterface)
                OutputInterface->PrintMsg("Simulation: no component at clicked location.");
            break;
        }

        Switch* sw = dynamic_cast<Switch*>(clickedComp);
        if (!sw)
        {
            if (OutputInterface)
                OutputInterface->PrintMsg("Simulation: click on a switch to toggle it.");
            break;
        }

        // Toggle the switch output state
        int current = sw->GetOutPinStatus();
        if (current == HIGH)
            sw->GetOutputPin()->setStatus(LOW);
        else
            sw->GetOutputPin()->setStatus(HIGH);

       
        int cc = GetCompCount();
        for (int pass = 0; pass < cc; ++pass)
        {
            for (int k = 0; k < cc; ++k)
            {
                Component* comp = GetComponent(k);
                if (!comp) continue;
                if (dynamic_cast<Switch*>(comp)) continue;
                comp->Operate();
            }
        }

        UpdateInterface();
        break;
    }

    case EXIT:
        return;
    case SIM_MODE:
        // Create simulation toolbar and redraw drawing area
        if (OutputInterface) {
            OutputInterface->CreateSimulationToolBar();
            OutputInterface->ClearDrawingArea();
        }
        // Redraw components in new mode (do NOT auto-close switches here)
        UpdateInterface();
        break;

        // Switch back to Design Mode toolbar (no Action object required)
    case DSN_MODE:
        if (OutputInterface) {
            OutputInterface->CreateDesignToolBar();
            OutputInterface->ClearDrawingArea();
        }
        UpdateInterface();
        break;

    }



    if (pAct)
    {
        pAct->Execute();
        delete pAct;
    }

    // After executing any action except SELECT → disable select mode
    if (ActType != SELECT)
        isSelectMode = false;
}

////////////////////////////////////////////////////////////////////
// Redraw interface
void ApplicationManager::UpdateInterface()
{
    OutputInterface->ClearDrawingArea();

    for (int i = 0; i < CompCount; i++)
        CompList[i]->Draw(OutputInterface);
}

////////////////////////////////////////////////////////////////////
// Getters
Input* ApplicationManager::GetInput() { return InputInterface; }
Output* ApplicationManager::GetOutput() { return OutputInterface; }

////////////////////////////////////////////////////////////////////
// Component hit testing
Component* ApplicationManager::GetComponentAt(int x, int y)
{
    for (int i = CompCount - 1; i >= 0; i--)
        if (CompList[i]->HitTest(x, y))
            return CompList[i];

    return nullptr;
}

////////////////////////////////////////////////////////////////////
// Selection control
void ApplicationManager::SelectComponent(Component* pComp)
{
    ClearSelection();
    selectedComponent = pComp;

    if (pComp)
        pComp->SetSelected(true);
}

void ApplicationManager::DeselectComponent()
{
    if (selectedComponent)
        selectedComponent->SetSelected(false);

    selectedComponent = nullptr;
}

Component* ApplicationManager::GetSelectedComponent() const
{
    return selectedComponent;
}

////////////////////////////////////////////////////////////////////
// Clear selection from everything
void ApplicationManager::ClearSelection()
{
    for (int i = 0; i < CompCount; i++)
        CompList[i]->SetSelected(false);

    selectedComponent = nullptr;
}

////////////////////////////////////////////////////////////////////
// Reset the internal single-selection pointer only (do NOT change component flags)
void ApplicationManager::ResetSelectedComponentPointer()
{
    selectedComponent = nullptr;
}

int ApplicationManager::GetCompCount() const
{
    return CompCount;
}
void ApplicationManager::BreakConnections(Component* pComp)
{
    // TODO: implement later
}

Component* ApplicationManager::GetComponent(int index) const
{
    if (index < 0 || index >= CompCount) return nullptr;
    return CompList[index];
}
void ApplicationManager::DeleteComponent(Component* pComp)
{
    if (!pComp) return;

    for (int i = 0; i < CompCount; i++)
    {
        if (CompList[i] == pComp)
        {
            delete CompList[i];

            for (int j = i; j < CompCount - 1; j++)
                CompList[j] = CompList[j + 1];

            CompList[CompCount - 1] = nullptr;
            CompCount--;
            return;
        }
    }
}

Component* ApplicationManager::GetComponentByPoint(int x, int y)
{
    for (int i = 0; i < CompCount; i++)
    {
        if (CompList[i]->HitTest(x, y))
            return CompList[i];
    }
    return nullptr;
}





void ApplicationManager::CreateTruthTable()
{
    // Fixed-size arrays (safe limits)
    const int MAX_INPUTS = 16;
    const int MAX_OUTPUTS = 16;

    Switch* inputs[MAX_INPUTS];
    LED* outputs[MAX_OUTPUTS];

    int inputCount = 0;
    int outputCount = 0;

    // Collect switches and LEDs
    for (int i = 0; i < CompCount; ++i)
    {
        Component* c = CompList[i];
        if (!c) continue;

        if (dynamic_cast<Switch*>(c) && inputCount < MAX_INPUTS)
            inputs[inputCount++] = (Switch*)c;
        else if (dynamic_cast<LED*>(c) && outputCount < MAX_OUTPUTS)
            outputs[outputCount++] = (LED*)c;
    }

    if (!OutputInterface)
        return;

    if (inputCount == 0)
    {
        OutputInterface->PrintMsg("Truth Table: no switches found.");
        return;
    }

    if (outputCount == 0)
    {
        OutputInterface->PrintMsg("Truth Table: no LEDs found.");
        return;
    }

    
    std::ofstream file("TruthTable.txt");
    if (!file.is_open())
    {
        OutputInterface->PrintMsg("Error: could not create TruthTable.txt");
        return;
    }

    // Header
    std::string header = "Inputs:";
    for (int i = 0; i < inputCount; ++i)
        header += " S" + std::to_string(i + 1);

    header += " | Outputs:";
    for (int j = 0; j < outputCount; ++j)
        header += " L" + std::to_string(j + 1);

    OutputInterface->PrintMsg(header);
    file << header << std::endl;

    // Generate truth table
    const int combos = 1 << inputCount;

    for (int mask = 0; mask < combos; ++mask)
    {
        // Set switch values
        for (int i = 0; i < inputCount; ++i)
        {
            int bit = (mask >> (inputCount - 1 - i)) & 1;
            inputs[i]->GetOutputPin()->setStatus(bit ? HIGH : LOW);
        }

        // Propagate signals
        for (int pass = 0; pass < CompCount; ++pass)
        {
            for (int k = 0; k < CompCount; ++k)
            {
                Component* comp = CompList[k];
                if (!comp) continue;
                if (dynamic_cast<Switch*>(comp)) continue;
                comp->Operate();
            }
        }

        // Build row
        std::string row = "";
        for (int i = 0; i < inputCount; ++i)
        {
            row += (inputs[i]->GetOutputPin()->getStatus() == HIGH ? '1' : '0');
            row += ' ';
        }

        row += "| ";

        for (int j = 0; j < outputCount; ++j)
        {
            row += (outputs[j]->GetInputPinStatus(1) == HIGH ? '1' : '0');
            row += ' ';
        }

        OutputInterface->PrintMsg(row);
        file << row << std::endl;
    }

    file.close();
    OutputInterface->PrintMsg("Truth Table saved to TruthTable.txt");
}
