#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "UI_Info.h"
#include "Components/Component.h"
#include "GUI/Input.h"
#include "GUI/Output.h"
#include <vector>
#include "Actions/SaveAction.h"
#include "Actions/LoadAction.h"
#include "Actions/AddProbing.h"




class Action;

class ApplicationManager
{
private:
    Component* clipboard[200];  // to store copied/cut components
    int clipboardCount;          // number of components in clipboard
    enum { MaxCompCount = 200 };
    Component* CompList[MaxCompCount];
    int CompCount;

    Component* selectedComponent;

    Input* InputInterface;
    Output* OutputInterface;

    bool isSelectMode; // <-- FIXED: renamed from isSelectingMode

public:
    void CreateTruthTable();
    ApplicationManager();
    ~ApplicationManager();
    void DeleteComponent(Component* pComp);
    void BreakConnections(Component* pComp);
    void ResetSelectedComponentPointer();
    // Component handling
    void AddComponent(Component* pComp);
    void SetClipboard(Component* comps[], int count); // store components to clipboard
    int GetClipboard(Component* outComps[]) const;    // retrieve clipboard components
    void RemoveComponent(Component* c);              // remove a component from CompList
    // Action handling
    ActionType GetUserAction();
    void ExecuteAction(ActionType);

    // Input / Output
    Input* GetInput();
    Output* GetOutput();

    // Selection system
    Component* GetComponentAt(int x, int y);
    void SelectComponent(Component* pComp);
    void DeselectComponent();
    Component* GetSelectedComponent() const;
    void ClearSelection();

    // Allow clearing the internal single-selection pointer without changing per-component flags
    // (used by multi-select so the manager's single-selected pointer doesn't interfere)
  

    // Redraw all
    void UpdateInterface();

    // Added accessors for use by actions / other modules
    int GetCompCount() const;
    Component* GetComponent(int index) const;

    // Returns a vector of all currently selected components
    std::vector<Component*> GetAllSelectedComponents() const;

    Component* GetComponentByPoint(int x, int y);

};

    // added getters for component array access so actions can inspect selections
#endif
// ===== Added for Delete / MultiDelete =====

