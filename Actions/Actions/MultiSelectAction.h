#ifndef MULTI_SELECT_ACTION_H
#define MULTI_SELECT_ACTION_H

#include "../Actions/Action.h"
#include "../Components/Component.h"

class ApplicationManager;

class MultiSelectAction : public Action
{
public:
    MultiSelectAction(ApplicationManager* pApp);
    virtual ~MultiSelectAction();

    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    virtual void Undo() override;
    virtual void Redo() override;

private:
    void ToggleComponent(Component* pComp);
};

#endif