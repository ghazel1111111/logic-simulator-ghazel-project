#include "NOR2.h"
#include "..\GUI\Output.h"

NOR2::NOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) : Gate(2, r_FanOut)
{
	m_GfxInfo = r_GfxInfo;
}

void NOR2::Operate()
{
	STATUS in1 = m_InputPins[0].getStatus();
	STATUS in2 = m_InputPins[1].getStatus();

	if (in1 == LOW && in2 == LOW)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}

// Draws 2-input NOR gate
void NOR2::Draw(Output* pOut)
{
	pOut->DrawNOR2(m_GfxInfo, selected);

	if (!m_Label.empty())
		pOut->DrawComponentLabel(m_GfxInfo, m_Label);
}

int NOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}

int NOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();
}

void NOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
void NOR2::Save(ofstream& OutFile)
{
	OutFile << "NOR2 "
		<< m_GfxInfo.x1 << " "
		<< m_GfxInfo.y1 << " "
		<< m_GfxInfo.x2 << " "
		<< m_GfxInfo.y2 << " "
		<< m_Label << endl;
}

void NOR2::Load(ifstream& InFile)
{
	InFile >> m_GfxInfo.x1
		>> m_GfxInfo.y1
		>> m_GfxInfo.x2
		>> m_GfxInfo.y2;

	getline(InFile, m_Label); // read label (may be empty)
}
