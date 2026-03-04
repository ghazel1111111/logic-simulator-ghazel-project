#include "../Actions/MultiDelete.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../Components/Component.h"

MultiDelete::MultiDelete(ApplicationManager* pApp) : Action(pApp)
{
}

void MultiDelete::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("MultiDelete: Click components to toggle; click empty area to finish.");

    int x, y;

    while (true)
    {
        pIn->GetPointClicked(x, y);

        Component* hit = pManager->GetComponentAt(x, y);
        if (!hit)
            break;

        hit->SetSelected(!hit->IsSelected());

        pManager->ResetSelectedComponentPointer();
        pManager->UpdateInterface();
    }

    pOut->ClearStatusBar();
}

void MultiDelete::Execute()
{
    ReadActionParameters();

    for (int i = pManager->GetCompCount() - 1; i >= 0; i--)
    {
        Component* comp = pManager->GetComponent(i);
        if (comp && comp->IsSelected())
        {
            pManager->BreakConnections(comp);
            pManager->DeleteComponent(comp);
        }
    }

    pManager->UpdateInterface();
}

void MultiDelete::Undo()
{
   
}

void MultiDelete::Redo()
{
    
}
