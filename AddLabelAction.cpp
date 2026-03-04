#include "AddLabelAction.h"
#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

AddLabelAction::AddLabelAction(ApplicationManager* pApp)
    : Action(pApp), selectedComponent(nullptr) {
}

AddLabelAction::~AddLabelAction() {}

void AddLabelAction::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("choose a component or a connetion to label.");

    int x, y;
    pIn->GetPointClicked(x, y);

    selectedComponent = pManager->GetComponentAt(x, y);
    if (!selectedComponent)
    {
        pOut->PrintMsg("no component selected");
        return;
    }

    pOut->PrintMsg("ENTER the label name");
    label = pIn->GetSrting(pOut);
    if (label.empty())
        pOut->PrintMsg("no component selected");
}

void AddLabelAction::Execute()
{
    ReadActionParameters();
    if (selectedComponent && !label.empty())
    {
        selectedComponent->SetLabel(label);
        pManager->UpdateInterface();
    }
}