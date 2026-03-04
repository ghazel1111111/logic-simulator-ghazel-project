#include "AND2.h"
#include "..\GUI\Output.h"

AND2::AND2(const GraphicsInfo &r_GfxInfo, int r_FanOut)
    : Gate(2, r_FanOut) // 2-input AND gate
{
    m_GfxInfo = r_GfxInfo;
}

void AND2::Operate()
{
    // AND2 gate: output is HIGH only if both inputs are HIGH
    int in1 = m_InputPins[0].getStatus();
    int in2 = m_InputPins[1].getStatus();
    if (in1 == HIGH && in2 == HIGH)
        m_OutputPin.setStatus(HIGH);
    else
        m_OutputPin.setStatus(LOW);
}

void AND2::Draw(Output* pOut)
{
    // Draw the 2-input AND gate
    pOut->DrawAND2(m_GfxInfo, selected);
    // Draw label if any
    if (!m_Label.empty())
        pOut->DrawComponentLabel(m_GfxInfo, m_Label);
}

int AND2::GetOutPinStatus()
{
    return m_OutputPin.getStatus();
}

int AND2::GetInputPinStatus(int n)
{
    if (n >= 1 && n <= 2)
        return m_InputPins[n - 1].getStatus();
    return -1;
}

void AND2::setInputPinStatus(int n, STATUS s)
{
    if (n >= 1 && n <= 2)
        m_InputPins[n - 1].setStatus(s);
}

void AND2::Save(ofstream& OutFile)
{
    OutFile << "AND2 "
        << m_GfxInfo.x1 << " "
        << m_GfxInfo.y1 << " "
        << m_GfxInfo.x2 << " "
        << m_GfxInfo.y2 << " "
        << m_Label << endl;
}

void AND2::Load(ifstream& InFile)
{
    InFile >> m_GfxInfo.x1
        >> m_GfxInfo.y1
        >> m_GfxInfo.x2
        >> m_GfxInfo.y2;

    getline(InFile, m_Label); // read label (may be empty)
}
