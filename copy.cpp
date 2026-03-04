#include "Defs.h"
#include "copy.h"
#include "ApplicationManager.h" 
#include <string>

CopyAction::CopyAction(ApplicationManager* pApp)
    : Action(pApp)
    , clipboardCount(0)
    , selected(nullptr)
{
    for (int i = 0; i < COPY_CLIPBOARD_MAX; ++i)
        clipboard[i] = nullptr;
}

void CopyAction::ReadActionParameters()
{
    // No parameters needed for copy
}

void CopyAction::Execute()
{
    // collect all selected components from the manager
    clipboardCount = 0;

    int count = pManager->GetCompCount();
    for (int i = 0; i < count && clipboardCount < COPY_CLIPBOARD_MAX; ++i)
    {
        Component* c = pManager->GetComponent(i);
        if (c && c->IsSelected())
            clipboard[clipboardCount++] = c;
    }

    if (clipboardCount == 0)
    {
        pManager->GetOutput()->PrintMsg("No component is selected");
        return;
    }

  
    pManager->GetOutput()->PrintMsg(std::to_string(clipboardCount) + " components copied");
    pManager->ClearSelection();
}

void CopyAction::Undo()
{
    // Copy-only action: nothing to undo
}

void CopyAction::Redo()
{
    // Nothing to redo
}