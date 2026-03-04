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
    // لا حاجة هنا
}

void SaveAction::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    // طلب اسم الملف من المستخدم
    pOut->PrintMsg("Enter file name (without extension):");
    std::string fileName = pIn->GetSrting(pOut);

    if (fileName.empty())
    {
        pOut->PrintMsg("Save cancelled.");
        return;
    }

    // إضافة الامتداد تلقائياً
    fileName += ".txt";

    std::ofstream OutFile(fileName);
    if (!OutFile)
    {
        pOut->PrintMsg("Error opening file!");
        return;
    }

    int count = pManager->GetCompCount();
    OutFile << count << std::endl;

    // حفظ كل المكونات (بما فيها Gates وConnections)
    for (int i = 0; i < count; i++)
    {
        Component* pComp = pManager->GetComponent(i);
        if (pComp)
            pComp->Save(OutFile); // كل component يكتب بياناته + نوعه
    }

    OutFile.close();
    pOut->PrintMsg("Circuit saved successfully.");
}


