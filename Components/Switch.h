#ifndef _Switch_H
#define _Switch_H
#define Switch_FANOUT 5 // default maximum number of outputs

/*
  Class Switch
  ----------- 
  represent a switch component: no input pins, a single output pin with a configurable fanout
*/

#include "Gate.h"

class Switch : public Gate
{
public:
	Switch(const GraphicsInfo& r_GfxInfo, int r_FanOut);
	virtual void Operate();	// updates output if needed (no-op for a hardware-style toggle switch)

	virtual void Draw(Output* pOut);	// Draws switch

	virtual int GetOutPinStatus();	//returns status of output pin
	virtual int GetInputPinStatus(int n);	//Switch has no input pins - returns -1

	virtual void setInputPinStatus(int n, STATUS s);	//no-op for Switch (no inputs)

	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);

};

#endif


