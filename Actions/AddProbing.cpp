#include "AddProbing.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../Components/Component.h"
#include "../Components/Gate.h"
#include "../Components/LED.h"
#include "../Components/Switch.h"
#include "../Components/Connection.h"


AddProbing::AddProbing(ApplicationManager* pApp)
    : Action(pApp)
{
}

void AddProbing::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMsg("Probing: click on a component");

    pIn->GetPointClicked(x, y);

    pOut->ClearStatusBar();
}

void AddProbing::Execute()
{
    ReadActionParameters();

    Output* pOut = pManager->GetOutput();
    if (!pOut) return;

    Component* comp = pManager->GetComponentByPoint(x, y);

    if (!comp)
    {
        pOut->PrintMsg("No component selected");
        return;
    }

    // لو Gate
    if (Gate* g = dynamic_cast<Gate*>(comp))
    {
        int out = g->GetOutPinStatus();
        pOut->PrintMsg("Gate output = " + std::to_string(out));
        return;
    }

    // لو LED
    if (LED* led = dynamic_cast<LED*>(comp))
    {
        int in = led->GetInputPinStatus(1);
        pOut->PrintMsg("LED status = " + std::to_string(in));
        return;
    }

    // لو Switch
    // لو Switch
    if (Switch* sw = dynamic_cast<Switch*>(comp))
    {
        int out = sw->GetOutPinStatus();
        pOut->PrintMsg("Switch output = " + std::to_string(out));
        return;
    }

    // ⭐ لو Connection
    if (Connection* conn = dynamic_cast<Connection*>(comp))
    {
        int val = conn->GetInputPinStatus(1);
        pOut->PrintMsg("Connection signal = " + std::to_string(val));
        return;
    }

    pOut->PrintMsg("Unknown component");

}
