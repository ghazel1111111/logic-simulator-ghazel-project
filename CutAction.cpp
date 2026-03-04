#include "CutAction.h"
#include "ApplicationManager.h"
#include "GUI/Output.h"

CutAction::CutAction(ApplicationManager* pApp)
    : Action(pApp), cutCount(0)
{
    for (int i = 0; i < 200; ++i)
        cutComponents[i] = nullptr;
}

void CutAction::ReadActionParameters()
{
    // No parameters needed; just operates on selected components
}

void CutAction::Execute()
{
    ApplicationManager* mgr = pManager;
    Output* pOut = mgr->GetOutput();

    cutCount = 0;
    int compCount = mgr->GetCompCount();
    Component* temp[200];

    for (int i = 0; i < compCount && cutCount < 200; i++)
    {
        Component* c = mgr->GetComponent(i);
        if (c && c->IsSelected())
            temp[cutCount++] = c;
    }

    if (cutCount == 0)
    {
        pOut->PrintMsg("No component selected for cut");
        return;
    }

    // Store in clipboard
    mgr->SetClipboard(temp, cutCount);

    // Remove from design
    for (int i = 0; i < cutCount; i++)
        mgr->RemoveComponent(temp[i]);

    mgr->ClearSelection();
    mgr->UpdateInterface();

    pOut->PrintMsg(std::to_string(cutCount) + " component(s) cut to clipboard");
}

void CutAction::Undo()
{
    // Optional: can implement undo later
}

void CutAction::Redo()
{
    // Optional: can implement redo later
}
