#include "EditLabelAction.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

EditLabelAction::EditLabelAction(ApplicationManager* pApp) : Action(pApp), targetComponent(nullptr)
{
}

EditLabelAction::~EditLabelAction()
{
}

void EditLabelAction::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Edit Label: Click on a component to edit its label.");

    int x, y;
    pIn->GetPointClicked(x, y);

    targetComponent = pManager->GetComponentAt(x, y);

    if (!targetComponent)
    {
        pOut->PrintMsg("No component found at the clicked position.");
        return;
    }

    oldLabel = targetComponent->GetLabel();

    pOut->PrintMsg("Enter new label (Press Enter to confirm, ESC to cancel):");
    newLabel = pIn->GetSrting(pOut);
}

void EditLabelAction::Execute()
{
    ReadActionParameters();

    if (!targetComponent || newLabel.empty()) // canceled or nothing clicked
        return;

    targetComponent->SetLabel(newLabel);
    pManager->UpdateInterface();
}

void EditLabelAction::Undo()
{
    if (!targetComponent) return;
    targetComponent->SetLabel(oldLabel);
    pManager->UpdateInterface();
}

void EditLabelAction::Redo()
{
    if (!targetComponent) return;
    targetComponent->SetLabel(newLabel);
    pManager->UpdateInterface();
}