#include "ValidateAction.h"
#include "../ApplicationManager.h"
#include "../Components/Gate.h"
#include "../Components/LED.h"
#include "../Components/Switch.h"
#include "../Components/Connection.h"
#include "../Components/InputPin.h"
#include "../Components/OutputPin.h"
#include "../GUI/Output.h"
#include <string>

static std::string ComponentDisplayName(Component* c, const char* typeName)
{
    if (!c) return std::string(typeName);

    std::string lbl = c->GetLabel();
    if (!lbl.empty()) return lbl;

    // If no label, include the type and position so the user can identify it
    GraphicsInfo gi = c->GetGraphicsInfo();
    return std::string(typeName) + " at (" + std::to_string(gi.x1) + "," + std::to_string(gi.y1) + ")";
}

ValidateAction::ValidateAction(ApplicationManager* pApp) : Action(pApp) {}
ValidateAction::~ValidateAction() {}

void ValidateAction::Execute()
{
    Output* pOut = pManager->GetOutput();
    if (!pOut) return;

    int total = pManager->GetCompCount();

    // Iterate using arrays/indices (no std::vector) to comply with "without vectors"
    for (int i = 0; i < total; ++i)
    {
        Component* comp = pManager->GetComponent(i);
        if (!comp) continue;

        // skip Connection objects - they are links, not sources/consumers to validate here
        if (dynamic_cast<Connection*>(comp))
            continue;

        // 1) LED: must have its single input connected and must not be treated as a source
        if (LED* led = dynamic_cast<LED*>(comp))
        {
            const std::string name = ComponentDisplayName(led, "LED");
            InputPin* ip = led->GetInputPin(1);
            if (!ip || ip->getConnection() == nullptr)
            {
                pOut->PrintMsg(("Validation failed: LED '" + name + "' input is not connected.").c_str());
                led->SetSelected(true);
                pManager->UpdateInterface();
                return;
            }

            // Ensure LED has no outgoing connections (defensive)
            OutputPin* lop = led->GetOutputPin();
            if (lop && lop->GetConnectionCount() > 0)
            {
                pOut->PrintMsg(("Validation failed: LED '" + name + "' must not have outgoing connections.").c_str());
                led->SetSelected(true);
                pManager->UpdateInterface();
                return;
            }
            continue;
        }

        // 2) Gates: each input pin must have a connection; also recommend output to be connected
        if (Gate* gate = dynamic_cast<Gate*>(comp))
        {
            const std::string name = ComponentDisplayName(gate, "Gate");
            int inCount = gate->GetInputCount();
            for (int j = 1; j <= inCount; ++j)
            {
                InputPin* ip = gate->GetInputPin(j);
                if (!ip || ip->getConnection() == nullptr)
                {
                    pOut->PrintMsg(("Validation failed: Gate '" + name + "' has unconnected input pin #" + std::to_string(j) + ".").c_str());
                    gate->SetSelected(true);
                    pManager->UpdateInterface();
                    return;
                }
            }

            OutputPin* op = gate->GetOutputPin();
            if (op && op->GetConnectionCount() == 0)
            {
                pOut->PrintMsg(("Validation failed: Gate '" + name + "' output is not connected.").c_str());
                gate->SetSelected(true);
                pManager->UpdateInterface();
                return;
            }

            continue;
        }

        // 3) Switch: no minimum outgoing connections required, but must not exceed maximum
        if (Switch* sw = dynamic_cast<Switch*>(comp))
        {
            const std::string name = ComponentDisplayName(sw, "Switch");
            OutputPin* op = sw->GetOutputPin();

            const int MAX_SWITCH_OUTPUTS = 1; // per request
            if (op && op->GetConnectionCount() > MAX_SWITCH_OUTPUTS)
            {
                pOut->PrintMsg(("Validation failed: Switch '" + name + "' has more than " + std::to_string(MAX_SWITCH_OUTPUTS) + " output connection(s).").c_str());
                sw->SetSelected(true);
                pManager->UpdateInterface();
                return;
            }

            // No error if op->GetConnectionCount() == 0 (allowed)
            continue;
        }

    }

    pOut->PrintMsg("Validation passed: all components are properly connected.");
}