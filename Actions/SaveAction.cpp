#include "SaveAction.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include <fstream>
#include <string>

SaveAction::SaveAction(ApplicationManager* pApp)
    : Action(pApp)
{
}

void SaveAction::ReadActionParameters()
{
    
}

void SaveAction::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

   
    pOut->PrintMsg("Enter file name (without extension):");
    std::string fileName = pIn->GetSrting(pOut);

    if (fileName.empty())
    {
        pOut->PrintMsg("Save cancelled.");
        return;
    }

   
    fileName += ".txt";

    std::ofstream OutFile(fileName);
    if (!OutFile)
    {
        pOut->PrintMsg("Error opening file!");
        return;
    }

    int count = pManager->GetCompCount();
    OutFile << count << std::endl;

    
    for (int i = 0; i < count; i++)
    {
        Component* pComp = pManager->GetComponent(i);
        if (pComp)
            pComp->Save(OutFile); 
    }

    OutFile.close();
    pOut->PrintMsg("Circuit saved successfully.");
}


