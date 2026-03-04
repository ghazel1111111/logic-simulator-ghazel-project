#include "Input.h"
#include "Output.h"
#include <iostream>
#include <string>
using namespace std;

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}
bool Input::CheckEnterPressed() const
{
	return (GetAsyncKeyState(VK_RETURN) & 0x8000);
}

bool Input::CheckMouseClick() const
{
	return (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
}
void Input::GetPointClicked(int& x, int& y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output* pOut)
{


	string userInput = "";
	char c;
	


	while (true)
	{
		pWind->WaitKeyPress(c);

		// ESCAPE ? return empty string
		if (c == 27)
		{
			pOut->ClearStatusBar();
			return "";
		}

		// ENTER ? finish typing
		if (c == 13)
		{
			return userInput;
		}

		// BACKSPACE handling
		if (c == 8)
		{
			if (!userInput.empty())
				userInput.pop_back();
		}
		else
		{
			// Add normal character
			userInput.push_back(c);
		}

		pOut->PrintMsg(userInput);
	}

	return " ";
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_AND2: return ADD_AND_GATE_2;
			case ITM_NAND2: return ADD_NAND_GATE_2;
			case ITM_AND3: return ADD_AND_GATE_3;
			case ITM_NOR2: return ADD_NOR_GATE_2;
			case ITM_NOR3: return ADD_NOR_GATE_3;
			case ITM_XOR2: return ADD_XOR_GATE_2;
			case ITM_XOR3: return ADD_XOR_GATE_3;
			case ITM_XNOR2: return ADD_XNOR_GATE_2;
			case ITM_OR2: return ADD_OR_GATE_2;
			case ITM_SWITCH_TO_SIM: return SIM_MODE;
			case ITM_BUFF: return ADD_Buff;
			case ITM_INV: return ADD_INV;
			case ITM_LED: return ADD_LED;
			case ITM_CONNECTION: return ADD_CONNECTION;
			case ITM_LABEL: return ADD_Label;
			case ITM_EDIT_LABEL: return EDIT_Label;
			case ITM_SELECT: return SELECT;
			case ITM_DELETE: return DEL;
			case ITM_MOVE: return MOVE;
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_COPY: return COPY;
			case ITM_CUT: return CUT;
			case ITM_PASTE: return PASTE;
			case ITM_MULTI_SELECT: return MULTI_SELECT;
			case ITM_UNDO: return UNDO;
			case ITM_REDO: return REDO;
			case ITM_SWITCH: return ADD_Switch;
			case ITM_EXIT: return EXIT;

			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			// Do NOT return SELECT here. Selecting should only start when the user clicks the SELECT toolbar button.
			return DSN_TOOL;	// click in drawing area ? normal design area click (not selection)
		}

		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	else	//Application is in Simulation mode
	{

		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_VALIDATION: return Add_vildation;
			case ITM_OPERATION: return Add_operation;
			case ITM_TRUTH: return Create_TruthTable;
			case ITM_PROBING: return Add_probing;
			case ITM_DESIGN: return DSN_MODE;

			}
		}
		return SIM_MODE;	//This should be changed after creating the compelete simulation bar 
	}

}


Input::~Input()
{
}
