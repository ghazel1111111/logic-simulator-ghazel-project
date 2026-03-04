#include "XOR3.h"
#include "..\GUI\Output.h"

XOR3::XOR3(const GraphicsInfo& r_GfxInfo, int r_FanOut) : Gate(3, r_FanOut) // <-- fixed: 3 inputs
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void XOR3::Operate()
{
	STATUS in1 = m_InputPins[0].getStatus();
	STATUS in2 = m_InputPins[1].getStatus();
	STATUS in3 = m_InputPins[2].getStatus();

	int highCount =
		(in1 == HIGH) +
		(in2 == HIGH) +
		(in3 == HIGH);

	if (highCount % 2 == 1)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}


// Function Draw
// Draws 3-input XOR gate
void XOR3::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info.
	pOut->DrawXOR3(m_GfxInfo, selected);
	// Draw label if any
	if (!m_Label.empty())
		pOut->DrawComponentLabel(m_GfxInfo, m_Label);
}

//returns status of outputpin
int XOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XOR3::GetInputPinStatus(int n)
{
	if (n >= 1 && n <= 3)
		return m_InputPins[n - 1].getStatus();
	return -1;
}

//Set status of an input pin to HIGH or LOW
void XOR3::setInputPinStatus(int n, STATUS s)
{
	if (n >= 1 && n <= 3)
		m_InputPins[n - 1].setStatus(s);
}
void XOR3::Save(ofstream& OutFile)
{
	OutFile << "XOR3 "
		<< m_GfxInfo.x1 << " "
		<< m_GfxInfo.y1 << " "
		<< m_GfxInfo.x2 << " "
		<< m_GfxInfo.y2 << " "
		<< m_Label << endl;
}

void XOR3::Load(ifstream& InFile)
{
	InFile >> m_GfxInfo.x1
		>> m_GfxInfo.y1
		>> m_GfxInfo.x2
		>> m_GfxInfo.y2;

	getline(InFile, m_Label); // read label (may be empty)
}
