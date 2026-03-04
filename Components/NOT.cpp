#include "NOT.h"
#include "..\GUI\Output.h"

NOT::NOT(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut) // LED has a single input
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void NOT::Operate()
{
	STATUS in1 = m_InputPins[0].getStatus();

	if (in1 == HIGH)
		m_OutputPin.setStatus(LOW);
	else
		m_OutputPin.setStatus(HIGH);
}


// Function Draw
// Draws LED
void NOT::Draw(Output* pOut)
{
	// Call output class and pass LED drawing info to it.
	pOut->DrawINV(m_GfxInfo, selected);
	// Draw label if any
	if (!m_Label.empty())
		pOut->DrawComponentLabel(m_GfxInfo, m_Label);
}

// returns status of output pin
int NOT::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


// returns status of Input pin #n
int NOT::GetInputPinStatus(int n)
{
	// n starts from 1 but array index starts from 0.
	// Guard against invalid indices.
	if (n - 1 < 0 || n - 1 >= 1) // LED has exactly 1 input
		return LOW;
	return m_InputPins[n - 1].getStatus();
}

// Set status of an input pin to HIGH or LOW
void NOT::setInputPinStatus(int n, STATUS s)
{
	// Guard against invalid indices.
	if (n - 1 < 0 || n - 1 >= 1) // LED has exactly 1 input
		return;
	m_InputPins[n - 1].setStatus(s);
}
void NOT::Save(ofstream& OutFile)
{
	OutFile << "NOT "
		<< m_GfxInfo.x1 << " "
		<< m_GfxInfo.y1 << " "
		<< m_GfxInfo.x2 << " "
		<< m_GfxInfo.y2 << " "
		<< m_Label << endl;
}

void NOT::Load(ifstream& InFile)
{
	InFile >> m_GfxInfo.x1
		>> m_GfxInfo.y1
		>> m_GfxInfo.x2
		>> m_GfxInfo.y2;

	getline(InFile, m_Label); // read label (may be empty)
}
