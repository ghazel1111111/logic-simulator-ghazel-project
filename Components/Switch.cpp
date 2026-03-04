#include "Switch.h"

Switch::Switch(const GraphicsInfo& r_GfxInfo, int r_FanOut)
	: Gate(0, r_FanOut) // Switch has 0 input pins and a configurable fanout for its output
{
	m_GfxInfo = r_GfxInfo;
}

// For a switch the Operate() is effectively a no-op here.
// The switch output state should be controlled by UI/simulation actions (toggle), not by inputs.
void Switch::Operate()
{
	// Intentionally left blank: switch output is changed by user actions elsewhere (e.g., toggle)
}

// Draw the switch
void Switch::Draw(Output* pOut)
{
	// Pass the logical output state so the UI can draw open/closed appropriately.
	bool closed = (m_OutputPin.getStatus() == HIGH);
	pOut->DrawSwitch(m_GfxInfo, selected, closed);

	// Draw label if any
	if (!m_Label.empty())
		pOut->DrawComponentLabel(m_GfxInfo, m_Label);
}

// returns status of output pin
int Switch::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

// Switch has no input pins; return -1 for "not applicable"
int Switch::GetInputPinStatus(int n)
{
	(void)n;
	return -1;
}

// No-op: Switch has no input pins to set
void Switch::setInputPinStatus(int n, STATUS s)
{
	(void)n; (void)s;
	return;
}

void Switch::Save(ofstream& OutFile)
{
	OutFile << "SWITCH "
		<< m_GfxInfo.x1 << " "
		<< m_GfxInfo.y1 << " "
		<< m_GfxInfo.x2 << " "
		<< m_GfxInfo.y2 << " "
		<< m_Label << endl;
}

void Switch::Load(ifstream& InFile)
{
	InFile >> m_GfxInfo.x1
		>> m_GfxInfo.y1
		>> m_GfxInfo.x2
		>> m_GfxInfo.y2;

	getline(InFile, m_Label);
}
