#ifndef _LED_H
#define _LED_H

#include "Gate.h"

#define LED_FANOUT 5

class LED : public Gate
{
public:
    LED(const GraphicsInfo& r_GfxInfo, int r_FanOut);
    virtual void Operate();    // update on/off state from input
    virtual void Draw(Output* pOut);    // draw LED (on/off)
    virtual int GetOutPinStatus();    // LED has no output; return -1
    virtual int GetInputPinStatus(int n);
    virtual void setInputPinStatus(int n, STATUS s);
    virtual void Save(ofstream& OutFile);
    virtual void Load(ifstream& InFile);

private:
    bool isOn; // true if input == HIGH
};

#endif

