#ifndef _MULTIDELETE_H
#define _MULTIDELETE_H

#include "Action.h"
#include "../Components/Component.h"

class ApplicationManager;

class MultiDelete : public Action
{
public:
    MultiDelete(ApplicationManager* pApp);

    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    virtual void Undo() override;
    virtual void Redo() override;
};

#endif
