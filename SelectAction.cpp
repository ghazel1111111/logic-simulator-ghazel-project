#include "SelectAction.h"
#include "ApplicationManager.h"
#include "GUI/Output.h"
#include "GUI/Input.h"

SelectAction::SelectAction(ApplicationManager* pApp) : Action(pApp)
{
    selectedComponent = nullptr;
}

SelectAction::~SelectAction() {}

void SelectAction::ReadActionParameters()
{
   
    pManager->GetOutput()->PrintMsg("Select Mode: Click on a component to select it.");
}

void SelectAction::Execute()
{
    ReadActionParameters();     // Show message ONCE in status bar

    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    int x, y;
    pIn->GetPointClicked(x, y);  // Wait for user click

    HandleSelect(x, y);
    UpdateUI();

    pOut->ClearStatusBar();
}

void SelectAction::Undo()
{
    Deselect();
    pManager->UpdateInterface();
}

void SelectAction::Redo()
{
}

void SelectAction::Deselect()
{
   
    pManager->DeselectComponent();
    selectedComponent = nullptr;
}

void SelectAction::HandleSelect(int x, int y)
{
   
    Component* hit = pManager->GetComponentAt(x, y);
    Component* current = pManager->GetSelectedComponent();

  
    if (hit == nullptr)
    {
        pManager->ClearSelection();
        selectedComponent = nullptr;
        return;
    }

    
    if (hit == current)
    {
        pManager->DeselectComponent();
        selectedComponent = nullptr;
        return;
    }

    // Otherwise select the clicked component (this clears any previous selection)
    pManager->SelectComponent(hit);
    selectedComponent = hit;
}

void SelectAction::UpdateUI()
{
    pManager->UpdateInterface();
}
