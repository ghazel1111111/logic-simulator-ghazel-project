#ifndef SELECT_ACTION_H
#define SELECT_ACTION_H

#include "Actions/Action.h"
#include "Components/Component.h"

class ApplicationManager;

class SelectAction : public Action
{
private:
    Component* selectedComponent;

public:
    SelectAction(ApplicationManager* pApp);
    virtual ~SelectAction();

    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    virtual void Undo() override;
    virtual void Redo() override;

    void Deselect();
    void HandleSelect(int x, int y);
    void UpdateUI();
};

#endif
