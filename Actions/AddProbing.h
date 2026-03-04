#pragma once
#include "Action.h"

class AddProbing : public Action
{
private:
    int x, y;   // مكان الكليك

public:
    AddProbing(ApplicationManager* pApp);

    virtual void ReadActionParameters() override;
    virtual void Execute() override;

    virtual void Undo() override {}
    virtual void Redo() override {}
};
