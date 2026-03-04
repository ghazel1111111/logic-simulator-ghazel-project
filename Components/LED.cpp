#include "LED.h"
#include "..\GUI\Output.h"

LED::LED(const GraphicsInfo& r_GfxInfo, int r_FanOut)
    : Gate(1, r_FanOut) // LED has 1 input
    , isOn(false)
{
    m_GfxInfo = r_GfxInfo;
}

void LED::Operate()
{
    // Read input pin and update on/off state. LED does not drive further outputs.
    if (m_Inputs >= 1)
        isOn = (m_InputPins[0].getStatus() == HIGH);
}

void LED::Draw(Output* pOut)
{
    // Draw LED using the new lit parameter
    pOut->DrawLed(m_GfxInfo, selected, isOn);
    if (!m_Label.empty())
        pOut->DrawComponentLabel(m_GfxInfo, m_Label);
}

int LED::GetOutPinStatus()
{
    // LED is a terminal; no output pin to drive
    return -1;
}

int LED::GetInputPinStatus(int n)
{
    if (n - 1 < 0 || n - 1 >= 1)
        return LOW;
    return m_InputPins[n - 1].getStatus();
}

void LED::setInputPinStatus(int n, STATUS s)
{
    if (n - 1 < 0 || n - 1 >= 1)
        return;
    m_InputPins[n - 1].setStatus(s);
}

void LED::Save(ofstream& OutFile)
{
    OutFile << "LED "
            << m_GfxInfo.x1 << " "
            << m_GfxInfo.y1 << " "
            << m_GfxInfo.x2 << " "
            << m_GfxInfo.y2 << " "
            << m_Label << endl;
}

void LED::Load(ifstream& InFile)
{
    InFile >> m_GfxInfo.x1
           >> m_GfxInfo.y1
           >> m_GfxInfo.x2
           >> m_GfxInfo.y2;
    getline(InFile, m_Label);
}
