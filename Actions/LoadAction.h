#pragma once
#include "Action.h"
#include <fstream>

class LoadAction : public Action
{
public:
    LoadAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual void Undo() {}
    virtual void Redo() {}
};
