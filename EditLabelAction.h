#pragma once
#include "Actions/Action.h"
#include "Components/Component.h"
#include "ApplicationManager.h"

class EditLabelAction : public Action
{
private:
    Component* targetComponent;  // component to edit
    std::string oldLabel;        // store previous label for undo
    std::string newLabel;        // new label input by user

public:
    EditLabelAction(ApplicationManager* pApp);
    virtual ~EditLabelAction();

    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    virtual void Undo() override;
    virtual void Redo() override;
};
