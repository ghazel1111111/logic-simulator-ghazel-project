#include "Delete.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"

Delete::Delete(ApplicationManager* pApp)
    : Action(pApp)
{
}
void Delete::ReadActionParameters()
{
    
}

void Delete::Execute()
{
    bool deletedAny = false;

  
    for (int i = pManager->GetCompCount() - 1; i >= 0; i--)
    {
        Component* comp = pManager->GetComponent(i);
        if (comp && comp->IsSelected())
        {
            pManager->BreakConnections(comp);
            pManager->DeleteComponent(comp);
            deletedAny = true;
        }
    }

    
    if (!deletedAny)
    {
        Component* comp = pManager->GetSelectedComponent();
        if (!comp)
        {
            pManager->GetOutput()->PrintMsg("No component selected to delete.");
            return;
        }

        pManager->BreakConnections(comp);
        pManager->DeleteComponent(comp);
    }

    pManager->ClearSelection();
    pManager->UpdateInterface();
}

void Delete::Undo()
{
}

void Delete::Redo()
{
}
