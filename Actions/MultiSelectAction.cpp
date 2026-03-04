#include "../ApplicationManager.h"
#include "MultiSelectAction.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"

MultiSelectAction::MultiSelectAction(ApplicationManager* pApp) : Action(pApp)
{
}

MultiSelectAction::~MultiSelectAction()
{
}

void MultiSelectAction::ReadActionParameters()
{
    
    pManager->GetOutput()->PrintMsg("Multi-select: click components to toggle; click empty area to finish.");
}

void MultiSelectAction::Execute()
{
    ReadActionParameters();

    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    int x, y;
    // Keep allowing clicks until user clicks empty drawing area (no component) — that finishes multi-select
    while (true)
    {
        pIn->GetPointClicked(x, y); // wait for a click

        
        Component* hit = pManager->GetComponentAt(x, y);
        if (hit == nullptr)
            break;

       
        ToggleComponent(hit);

        // Ensure ApplicationManager's single-selection pointer won't interfere while multiple are selected
        pManager->ResetSelectedComponentPointer();

        // Update UI so user sees selection immediately
        pManager->UpdateInterface();
    }

    pOut->ClearStatusBar();
}

void MultiSelectAction::Undo()
{
   
}

void MultiSelectAction::Redo()
{
   
}

void MultiSelectAction::ToggleComponent(Component* pComp)
{
    if (!pComp) return;
    pComp->SetSelected(!pComp->IsSelected());
}