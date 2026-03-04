
#include "NOR3.h"
#include "..\GUI\Output.h"

NOR3::NOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut) : Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void NOR3::Operate()
{
	STATUS in1 = m_InputPins[0].getStatus();
	STATUS in2 = m_InputPins[1].getStatus();
	STATUS in3 = m_InputPins[2].getStatus();

	if (in1 == LOW && in2 == LOW && in3 == LOW)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}

// Function Draw
// Draws 3-input NOR gate
void NOR3::Draw(Output* pOut)
{
	// Pass selection state so Output can draw highlighted image when selected
	pOut->DrawNOR3(m_GfxInfo, selected);

	// Draw label if any
	if (!m_Label.empty())
		pOut->DrawComponentLabel(m_GfxInfo, m_Label);
}

int NOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();	
}

int NOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();
}

void NOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
void NOR3::Save(ofstream& OutFile)
{
	OutFile << "NOR3 "
		<< m_GfxInfo.x1 << " "
		<< m_GfxInfo.y1 << " "
		<< m_GfxInfo.x2 << " "
		<< m_GfxInfo.y2 << " "
		<< m_Label << endl;
}

void NOR3::Load(ifstream& InFile)
{
	InFile >> m_GfxInfo.x1
		>> m_GfxInfo.y1
		>> m_GfxInfo.x2
		>> m_GfxInfo.y2;

	getline(InFile, m_Label); // read label (may be empty)
}
