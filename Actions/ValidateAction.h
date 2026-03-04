#pragma once
#include "Action.h"

class ApplicationManager;

class ValidateAction : public Action
{
public:
    ValidateAction(ApplicationManager* pApp);
    virtual ~ValidateAction();

    // No parameters required from user
    virtual void ReadActionParameters() override {}

    // Perform validation
    virtual void Execute() override;

    // No undo/redo for this action
    virtual void Undo() override {}
    virtual void Redo() override {}
};
