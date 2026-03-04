#pragma once
#include "Actions/Action.h"
#include "Components/Component.h"

class ApplicationManager;

class CutAction : public Action
{
private:
    Component* cutComponents[200];
    int cutCount;

public:
    CutAction(ApplicationManager* pApp);
    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    virtual void Undo() override;
    virtual void Redo() override;
};
