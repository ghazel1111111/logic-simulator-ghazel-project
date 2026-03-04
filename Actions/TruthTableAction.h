#pragma once
#ifndef TRUTH_TABLE_ACTION_H
#define TRUTH_TABLE_ACTION_H
#include "Actions/Action.h"

class TruthTableAction : public Action
{
public:
    TruthTableAction(ApplicationManager* pApp);
    virtual void ReadActionParameters() {}
    virtual void Execute();
    virtual void Undo() {}
    virtual void Redo() {}
};
#endif
