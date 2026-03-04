#include "Actions/Action.h"
#include <vector>

class Component;
class ApplicationManager;

class MoveAction : public Action
{
public:
    MoveAction(ApplicationManager* pApp);
    virtual ~MoveAction();

    // Read the source and destination clicks
    virtual void ReadActionParameters() override;
    // Execute the move (translates component(s) by dx,dy)
    virtual void Execute() override;

    // No-op for now (can be implemented to support undo/redo)
    virtual void Undo() override {}
    virtual void Redo() override {}

private:
    int x1 = 0, y1 = 0; // source click
    int x2 = 0, y2 = 0; // destination click

    std::vector<Component*> targets; // components to move
};