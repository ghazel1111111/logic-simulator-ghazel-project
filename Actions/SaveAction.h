#pragma once
#include "Action.h"
#include <fstream>

class SaveAction : public Action
{
public:
    SaveAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();
    virtual void Execute();

    virtual void Undo() {}
    virtual void Redo() {}
};
