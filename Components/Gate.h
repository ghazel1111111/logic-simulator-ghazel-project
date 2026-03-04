#ifndef _GATE_H
#define _GATE_H

/*
  Class Gate
  -----------
  - Base class for all types of gates
  - Each gate has n inputs pins and one output pin
*/


#include "InputPin.h"
#include "OutputPin.h"
#include "Component.h"

class Gate:public Component
{
protected:
	InputPin* m_InputPins;	//Array of input pins of the Gate
	OutputPin m_OutputPin;	//The Gate output pin
	int m_Inputs;		//No. of input pins of that Gate.
public:
	Gate(int r_Inputs, int r_FanOut);
	OutputPin* GetOutputPin() { return &m_OutputPin; }
	int GetInputCount() const { return m_Inputs; }
	// Returns pointer to the n-th input pin (1-based index)
	InputPin* GetInputPin(int n) {
		if (n >= 1 && n <= m_Inputs && m_InputPins)
			return &m_InputPins[n - 1];
		return nullptr;
	}// Save / Load remain abstract for all gates

};

#endif
