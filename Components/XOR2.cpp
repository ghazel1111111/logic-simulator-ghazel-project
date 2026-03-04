#include "XOR2.h"
#include "..\GUI\Output.h"

XOR2::XOR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void XOR2::Operate()
{
	STATUS in1 = m_InputPins[0].getStatus();
	STATUS in2 = m_InputPins[1].getStatus();

	if (in1 != in2)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}


// Function Draw
// Draws 2-input AND gate
void XOR2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it, including selection state.
	pOut->DrawXOR2(m_GfxInfo, selected);
	// Draw label if any
	if (!m_Label.empty())
		pOut->DrawComponentLabel(m_GfxInfo, m_Label);
}

//returns status of outputpin
int XOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
void XOR2::Save(ofstream& OutFile)
{
	OutFile << "XOR2 "
		<< m_GfxInfo.x1 << " "
		<< m_GfxInfo.y1 << " "
		<< m_GfxInfo.x2 << " "
		<< m_GfxInfo.y2 << " "
		<< m_Label << endl;
}

void XOR2::Load(ifstream& InFile)
{
	InFile >> m_GfxInfo.x1
		>> m_GfxInfo.y1
		>> m_GfxInfo.x2
		>> m_GfxInfo.y2;

	getline(InFile, m_Label); // read label (may be empty)
}
