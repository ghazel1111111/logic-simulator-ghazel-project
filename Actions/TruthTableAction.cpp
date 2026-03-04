#include "../ApplicationManager.h"
#include "TruthTableAction.h"

TruthTableAction::TruthTableAction(ApplicationManager* pApp) : Action(pApp) {}

void TruthTableAction::Execute()
{
    pManager->CreateTruthTable();
}