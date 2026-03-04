#ifndef _NOT_H
#define _NOT_H

#define NOT_FANOUT 5 // You can adjust the value as needed for your design

#include "Gate.h"

class NOT : public Gate
{
public:
    NOT(const GraphicsInfo& r_GfxInfo, int r_FanOut);
    virtual void Operate();
    virtual void Draw(Output* pOut);

    virtual int GetOutPinStatus();
    virtual int GetInputPinStatus(int n);
    virtual void setInputPinStatus(int n, STATUS s);

    virtual void Save(ofstream& OutFile);
    virtual void Load(ifstream& InFile);
};

#endif



