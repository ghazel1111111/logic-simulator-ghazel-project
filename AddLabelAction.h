#pragma once
#include "Actions/Action.h"
#include "Components/Component.h"
#include <string>

class ApplicationManager;

class AddLabelAction : public Action
{
private:
    Component* selectedComponent;
    std::string label;

public:
    AddLabelAction(ApplicationManager* pApp);
    virtual ~AddLabelAction();

    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    virtual void Undo() override {}
    virtual void Redo() override {}
};

