#ifndef COMPONENT_H
#define COMPONENT_H

#include "..\Defs.h"
#include "..\GUI\Output.h"
#include "InputPin.h"
#include <fstream>
#include <string>

class Component
{
protected:
    GraphicsInfo m_GfxInfo;
    string m_Label;

    // NEW: selection flag
    bool selected;

public:
    Component();
    Component(const GraphicsInfo& r_GfxInfo);

    // single pure-virtual Operate
    virtual void Operate() = 0;
    virtual void Draw(Output* pOut) = 0;

    virtual GraphicsInfo GetGraphicsInfo() const;
    virtual void SetGraphicsInfo(GraphicsInfo r_GFX);

    // NEW: selection support (inline to avoid multiple-definition problems)
    void SetSelected(bool s) { selected = s; }
    bool IsSelected() const { return selected; }

    virtual bool HitTest(int x, int y);

    virtual int GetOutPinStatus() = 0;
    virtual int GetInputPinStatus(int n) = 0;
    virtual void setInputPinStatus(int n, STATUS s) = 0;
    

    void SetLabel(const string& L) { m_Label = L; }
    string GetLabel() const { return m_Label; }

    // --- Pin location virtuals (needed for moving connections) ---
    virtual void GetInputPinPosition(int n, int& x, int& y) { x = y = 0; }
    virtual void GetOutputPinPosition(int& x, int& y) { x = y = 0; }
    virtual int GetInputPinIndex(InputPin* pin) { return -1; }

    // ===== SAVE / LOAD =====
    virtual void Save(std::ofstream& out);
    virtual void Load(std::ifstream& in);

    // single virtual destructor
    virtual ~Component() = default;
};

#endif