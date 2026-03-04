#pragma once
#include "../Defs.h"
#include "Component.h"
#include "../GUI/Output.h"
#include "InputPin.h"
#include "OutputPin.h"
#include "Connection.h"
#include <iostream>

class Connection : public Component
{
private:
    OutputPin* SrcPin;
    InputPin* DstPin;
    bool straight;
public:
    Connection(const GraphicsInfo& r_GfxInfo,
        OutputPin* pSrcPin,
        InputPin* pDstPin);

    virtual ~Connection(); // <-- Add this line

    void setSourcePin(OutputPin* pSrcPin);
    OutputPin* getSourcePin();

    void setDestPin(InputPin* pDstPin);
    InputPin* getDestPin();

    virtual void Operate() override;
    virtual void Draw(Output* pOut) override;

    virtual int GetOutPinStatus() override;
    virtual int GetInputPinStatus(int n) override;
    virtual void setInputPinStatus(int n, STATUS s) override;

    void UpdatePosition();

    virtual void Save(ofstream& OutFile) override;
    virtual void Load(ifstream& InFile) override;
    virtual bool HitTest(int x, int y) override; 

    // Add this to fix the abstract class error:

};