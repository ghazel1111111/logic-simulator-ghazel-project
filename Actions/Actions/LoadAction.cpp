#include "LoadAction.h"
#include "..\ApplicationManager.h"
#include "..\Components\Connection.h"
#include "..\Components\AND2.h"
#include "..\Components\AND3.h"
#include "..\Components\NOR2.h"
#include "..\Components\NOR3.h"
#include "..\Components\OR2.h"
#include "..\Components\XOR2.h"
#include "..\Components\XOR3.h"
#include "..\Components\NAND2.h"
#include "..\Components\NOT.h"
#include "..\Components\LED.h"
#include "..\Components\XNOR2.h"
#include "..\Components\buffer.h"
#include "..\Components\Switch.h"
#include <fstream>
#include <string>

LoadAction::LoadAction(ApplicationManager* pApp)
    : Action(pApp)
{
}

void LoadAction::ReadActionParameters()
{
    // لا حاجة هنا
}

// دالة لإنشاء المكون حسب نوعه
Component* CreateComponentByType(const std::string& type)
{
    if (type == "AND2") return new AND2(GraphicsInfo{}, AND2_FANOUT);
    if (type == "AND3") return new AND3(GraphicsInfo{}, AND3_FANOUT);
    if (type == "NOR2") return new NOR2(GraphicsInfo{}, NOR2_FANOUT);
    if (type == "NOR3") return new NOR3(GraphicsInfo{}, NOR3_FANOUT);
    if (type == "OR2") return new OR2(GraphicsInfo{}, OR2_FANOUT);
    if (type == "XOR2") return new XOR2(GraphicsInfo{}, XOR2_FANOUT);
    if (type == "XOR3") return new XOR3(GraphicsInfo{}, XOR3_FANOUT);
    if (type == "NAND2") return new NAND2(GraphicsInfo{}, NAND2_FANOUT);
    if (type == "NOT") return new NOT(GraphicsInfo{}, NOT_FANOUT);
    if (type == "LED") return new LED(GraphicsInfo{}, LED_FANOUT);
    if (type == "XNOR2") return new XNOR2(GraphicsInfo{}, XNOR2_FANOUT);
    if (type == "buffer") return new buffer(GraphicsInfo{}, buffer_FANOUT);
    if (type == "SWITCH") return new Switch(GraphicsInfo{}, Switch_FANOUT);
    if (type == "CONNECTION") return new Connection(GraphicsInfo{}, nullptr, nullptr);

    return nullptr;
}

void LoadAction::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Enter file name to load (without extension):");
    std::string fileName = pIn->GetSrting(pOut);

    if (fileName.empty())
    {
        pOut->PrintMsg("Load cancelled.");
        return;
    }

    fileName += ".txt";
    std::ifstream InFile(fileName);
    if (!InFile)
    {
        pOut->PrintMsg("File not found!");
        return;
    }

    // مسح المكونات القديمة
    int oldCount = pManager->GetCompCount();
    for (int i = oldCount - 1; i >= 0; i--)
        pManager->DeleteComponent(pManager->GetComponent(i));

    int count;
    InFile >> count;
    std::string type;

    for (int i = 0; i < count; i++)
    {
        InFile >> type;
        Component* pComp = CreateComponentByType(type);

        if (pComp)
        {
            pComp->Load(InFile);
            pManager->AddComponent(pComp);
        }
        else
        {
            std::string dummy;
            getline(InFile, dummy); // تجاهل السطر إذا النوع غير معروف
        }
    }

    InFile.close();
    pManager->UpdateInterface();
    pOut->PrintMsg("Circuit loaded successfully.");
}
