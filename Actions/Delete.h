#ifndef DELETE_H
#define DELETE_H

#include "Action.h"

class ApplicationManager;

class Delete : public Action
{
public:
    Delete(ApplicationManager* pApp);
    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    virtual void Undo() override;
    virtual void Redo() override;
};

#endif
