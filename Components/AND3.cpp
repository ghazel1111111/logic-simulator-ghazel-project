#include "AND3.h"
#include "..\GUI\Output.h"

// Constructor
AND3::AND3(const GraphicsInfo& r_GfxInfo, int r_FanOut)
    : Gate(3, r_FanOut) // 3-inputs
{
    m_GfxInfo = r_GfxInfo;
}

// Calculates the output of the AND gate
void AND3::Operate()
{
    // AND3: output is HIGH only if all 3 inputs are HIGH
    STATUS in1 = m_InputPins[0].getStatus();
    STATUS in2 = m_InputPins[1].getStatus();
    STATUS in3 = m_InputPins[2].getStatus();
    if (in1 == HIGH && in2 == HIGH && in3 == HIGH)
        m_OutputPin.setStatus(HIGH);
    else
        m_OutputPin.setStatus(LOW);
}

// Draws 3-input AND gate
void AND3::Draw(Output* pOut)
{
    pOut->DrawAND3(m_GfxInfo, selected);
    pOut->DrawComponentLabel(m_GfxInfo, m_Label);
}

// returns status of outputpin if LED, return -1
int AND3::GetOutPinStatus()
{
    return m_OutputPin.getStatus();
}

// returns status of Inputpin # n if SWITCH, return -1
int AND3::GetInputPinStatus(int n)
{
    if (n >= 1 && n <= 3)
        return m_InputPins[n - 1].getStatus();
    return -1;
}

// set status of Inputpin # n, to be used by connection class.
void AND3::setInputPinStatus(int n, STATUS s)
{
    if (n >= 1 && n <= 3)
        m_InputPins[n - 1].setStatus(s);
}
void AND3::Save(ofstream& OutFile)
{
    OutFile << "AND3 "
        << m_GfxInfo.x1 << " "
        << m_GfxInfo.y1 << " "
        << m_GfxInfo.x2 << " "
        << m_GfxInfo.y2 << " "
        << m_Label << endl;
}

void AND3::Load(ifstream& InFile)
{
    InFile >> m_GfxInfo.x1
        >> m_GfxInfo.y1
        >> m_GfxInfo.x2
        >> m_GfxInfo.y2;

    getline(InFile, m_Label); // read label (may be empty)
}
