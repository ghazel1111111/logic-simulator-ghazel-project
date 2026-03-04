#ifndef ACTIONS_ADDCONNECTION_H
#define ACTIONS_ADDCONNECTION_H

#include "Action.h"

class ApplicationManager; // forward declaration

class AddConnection : public Action
{
private:
    // Coordinates captured from user clicks
    int x1, y1; // source click
    int x2, y2; // destination click

public:
    // Constructor
    AddConnection(ApplicationManager* pApp);

    // Destructor
    virtual ~AddConnection() = default;

    // Reads parameters required for action to execute (e.g., two clicks)
    virtual void ReadActionParameters() override;

    // Execute action (create connection and add to application manager)
    virtual void Execute() override;

    // Optional undo/redo hooks (default no-op; override in .cpp if needed)
    virtual void Undo() override {}
    virtual void Redo() override {}
};

#endif // ACTIONS_ADDCONNECTION_H
