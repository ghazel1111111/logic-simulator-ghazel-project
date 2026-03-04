#ifndef COPY_H
#define COPY_H

#include "Defs.H"
#include "Actions/Action.h"
#include "Components/Component.h"

// fixed-size clipboard (no std::vector)
constexpr int COPY_CLIPBOARD_MAX = 200;

class CopyAction : public Action
{
public:
    CopyAction(ApplicationManager* pApp);
    virtual void ReadActionParameters() override;
    virtual void Execute() override;
    virtual void Undo() override;
    virtual void Redo() override;

private:
    Component* clipboard[COPY_CLIPBOARD_MAX];
    int clipboardCount;
    Component* selected;
};

#endif // COPY_H
