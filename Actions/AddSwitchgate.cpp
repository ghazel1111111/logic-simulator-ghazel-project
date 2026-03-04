#include "AddSwitchgate.h"
#include "..\ApplicationManager.h"

AddSwitchgate::AddSwitchgate(ApplicationManager* pApp) :Action(pApp)
{
}

AddSwitchgate::~AddSwitchgate(void)
{
}

void AddSwitchgate::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Switch: Click to add the switch");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();
}

void AddSwitchgate::Execute()
{
	//Get Center point of the Switch
	ReadActionParameters();

	//Calculate the rectangle Corners using existing UI sizes
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the Switch

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;

	// Use the Switch-specific fanout constant
	Switch* pA = new Switch(GInfo, Switch_FANOUT);
	pManager->AddComponent(pA);
}

void AddSwitchgate::Undo()
{
}

void AddSwitchgate::Redo()
{
}

