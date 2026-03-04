#include "MoveAction.h"
#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"
#include "GUI/Input.h"
#include <algorithm>

MoveAction::MoveAction(ApplicationManager * pApp) : Action(pApp)
{
}

MoveAction::~MoveAction()
{
}

void MoveAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMsg("Move: Click a component to start moving (or click a selected component to move all selected).");
	pIn->GetPointClicked(x1, y1);

	Component* hit = pManager->GetComponentAt(x1, y1);
	if (!hit)
	{
		pOut->PrintMsg("No component clicked. Move cancelled.");
		return;
	}

	// If clicked component is selected, move all selected components
	if (hit->IsSelected())
	{
		for (int i = 0; i < pManager->GetCompCount(); ++i)
		{
			Component* c = pManager->GetComponent(i);
			if (c && c->IsSelected())
				targets.push_back(c);
		}
	}
	else
	{
		// move only the clicked component
		targets.push_back(hit);
	}

	pOut->PrintMsg("Move: Click destination point.");
	pIn->GetPointClicked(x2, y2);

	pOut->ClearStatusBar();
}

void MoveAction::Execute()
{
	ReadActionParameters();

	if (targets.empty())
		return;

	int dx = x2 - x1;
	int dy = y2 - y1;

	for (Component* c : targets)
	{
		if (!c) continue;
		GraphicsInfo gi = c->GetGraphicsInfo();
		gi.x1 += dx;
		gi.x2 += dx;
		gi.y1 += dy;
		gi.y2 += dy;
		c->SetGraphicsInfo(gi);
	}

	// Redraw interface
	pManager->UpdateInterface();
}