#include "AddConnection.h"
#include "..\ApplicationManager.h"
#include "..\Components\Connection.h"
#include "..\Components\Gate.h"
#include "..\Components\LED.h"
#include "..\Components\Switch.h"
static std::string LabelOrType(Component* c, const char* fallback) //done
{
    if (!c) return std::string(fallback);
    std::string lbl = c->GetLabel();
    if (!lbl.empty()) return lbl;
    return std::string(fallback);
}
AddConnection::AddConnection(ApplicationManager* pApp) : Action(pApp) {}

void AddConnection::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Click the OUTPUT pin");
    pIn->GetPointClicked(x1, y1);

    pOut->PrintMsg("Click the INPUT pin");
    pIn->GetPointClicked(x2, y2);

    pOut->ClearStatusBar();
}

void AddConnection::Execute()
{
    ReadActionParameters();
    Output* pOut = pManager->GetOutput(); 
    Component* SrcCmp = pManager->GetComponentAt(x1, y1);
    Component* DstCmp = pManager->GetComponentAt(x2, y2);

    if (!SrcCmp || !DstCmp)
        return;

    // ===== GET SOURCE PIN =====
    OutputPin* pSrcPin = nullptr;

    if (Switch* sw = dynamic_cast<Switch*>(SrcCmp))
        pSrcPin = sw->GetOutputPin();

    else if (Gate* gate = dynamic_cast<Gate*>(SrcCmp))
        pSrcPin = gate->GetOutputPin();

    if (!pSrcPin)
        return;

    // ===== GET DEST PIN =====
    InputPin* pDstPin = nullptr;
    if (LED* ledSrc = dynamic_cast<LED*>(SrcCmp))
    {
        std::string name = LabelOrType(ledSrc, "Unnamed LED");
        pOut->PrintMsg(("Error: LED '" + name + "' cannot be used as a source. LEDs only accept inputs.").c_str());
        return;
    }
    else if (Gate* gate = dynamic_cast<Gate*>(DstCmp))
    {
        int count = gate->GetInputCount();

        // detect input pin based on Y click
        GraphicsInfo GI = gate->GetGraphicsInfo();
        int pinH = (GI.y2 - GI.y1) / (count + 1);

        for (int i = 1; i <= count; i++)
        {
            int pinY = GI.y1 + i * pinH;

            if (abs(y2 - pinY) <= 10)
            {
                pDstPin = gate->GetInputPin(i);
                break;
            }
        }

        if (!pDstPin)
            pDstPin = gate->GetInputPin(1);
    }

    if (!pDstPin)
        return;
    if (pDstPin->getConnection() != nullptr)
    {
        pOut->PrintMsg("Error: Destination input pin already connected.");
        return;
    } //done
    // ===== CREATE CONNECTION =====
    GraphicsInfo G;
    G.x1 = x1;
    G.y1 = y1;
    G.x2 = x2;
    G.y2 = y2;

    Connection* pConn = new Connection(G, pSrcPin, pDstPin);

    // Attempt to connect source output -> connection exactly once.
    if (!pSrcPin->ConnectTo(pConn))
    {
        // failed due to fan-out limit (general)
        pOut->PrintMsg("Error: Source output pin fan-out limit reached.");
        delete pConn;
        return;
    }

    // Link destination pin to the connection
    pDstPin->setConnection(pConn);

    // Add connection component to manager
    pManager->AddComponent(pConn);
}