#include "Output.h"

Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = RED;
	UI.ConnColor = BLUE;
	UI.MsgColor = BLUE;
	UI.BkGrndColor = WHITE;

	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	ChangeTitle("Programming Techniques Project");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar

}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(UI.MsgColor);
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void Output::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::deletetoolbar() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
	/*
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);*/
}

void Output::CreateDesignToolBar() const
{
	deletetoolbar();
	UI.AppMode = DESIGN;	//Design Mode

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_AND2] = "Images\\Menu\\AND.jpg";
	MenuItemImages[ITM_AND3] = "Images\\Menu\\AND3.jpg";
	MenuItemImages[ITM_NAND2] = "Images\\Menu\\NAND.jpg";
	MenuItemImages[ITM_OR2] = "Images\\Menu\\OR.jpg";
	MenuItemImages[ITM_NOR2] = "Images\\Menu\\NOR.jpg";
	MenuItemImages[ITM_NOR3] = "Images\\Menu\\NOR3.jpg";
	MenuItemImages[ITM_XOR2] = "Images\\Menu\\XOR.jpg";
	MenuItemImages[ITM_XOR3] = "Images\\Menu\\XOR3.jpg";
	MenuItemImages[ITM_XNOR2] = "Images\\Menu\\XNOR.jpg";
	MenuItemImages[ITM_BUFF] = "Images\\Menu\\Buffer.jpg";
	MenuItemImages[ITM_INV] = "Images\\Menu\\Inverter.jpg";
	MenuItemImages[ITM_LED] = "Images\\Menu\\LED.jpg";
	MenuItemImages[ITM_CONNECTION] = "Images\\Menu\\Connection.jpg";
	MenuItemImages[ITM_LABEL] = "Images\\Menu\\Label.jpg";
	MenuItemImages[ITM_EDIT_LABEL] = "Images\\Menu\\Edit_Label.jpg";
	MenuItemImages[ITM_SELECT] = "Images\\Menu\\Select.jpg";
	MenuItemImages[ITM_DELETE] = "Images\\Menu\\Delete.jpg";
	MenuItemImages[ITM_MOVE] = "Images\\Menu\\Move.jpg";
	MenuItemImages[ITM_SAVE] = "Images\\Menu\\Save.jpg";
	MenuItemImages[ITM_LOAD] = "Images\\Menu\\Load.jpg";
	MenuItemImages[ITM_COPY] = "Images\\Menu\\Copy.jpg";
	MenuItemImages[ITM_CUT] = "Images\\Menu\\Cut.jpg";
	MenuItemImages[ITM_PASTE] = "Images\\Menu\\Paste.jpg";
	MenuItemImages[ITM_MULTI_SELECT] = "Images\\Menu\\Multi_selection.jpg";
	MenuItemImages[ITM_UNDO] = "Images\\Menu\\Undo.jpg";
	MenuItemImages[ITM_REDO] = "Images\\Menu\\Redo.jpg";
	MenuItemImages[ITM_SWITCH_TO_SIM] = "Images\\Menu\\Switch_To_Sim.jpg";
	MenuItemImages[ITM_SWITCH] = "Images\\Menu\\Switch.jpg";
	MenuItemImages[ITM_EXIT] = "Images\\Menu\\Exit.jpg";
	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i < ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);


}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	deletetoolbar();
	UI.AppMode = SIMULATION;	//Simulation Mode
	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)

	string MenuItemImages[ITM_SIM_CNT];

	/*MenuItemImages[ITM_SIM] = "Images\\Menu\\Simulate.jpg";*/
	MenuItemImages[ITM_VALIDATION] = "Images\\Menu\\Validation.jpg";
	MenuItemImages[ITM_OPERATION] = "Images\\Menu\\Simulate_Operation.jpg";
	MenuItemImages[ITM_TRUTH] = "Images\\Menu\\Truth_Table.jpg";
	MenuItemImages[ITM_PROBING] = "Images\\Menu\\Probing.jpg";
	MenuItemImages[ITM_DESIGN] = "Images\\Menu\\Design.jpg";


	for (int i = 0; i < ITM_SIM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const//done
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND_Hi.jpg";
	else
		GateImage = "Images\\Gates\\AND.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const //done
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NAND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\NAND.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_OR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\OR.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\NOR.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\XOR.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XNOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\XNOR.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawBUFF(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_BUFFER_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Buffer.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawINV(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_INV_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Inverter.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Menu\\NOR_HI.jpg";
	else
		GateImage = "Images\\Gates\\NOR3.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawSwitch(GraphicsInfo r_GfxInfo, bool selected, bool closed) const
{
	// Choose image based on logical state (closed == ON/HIGH) and selection.
	// If you have distinct highlighted images for open/closed, replace paths accordingly.
	string GateImage;
	if (selected) {
		// use the toolbar/selected image for highlight (keeps current behavior)
		GateImage = "Images\\Menu\\Switch.jpg";
	}
	else if (closed) {
		// switch closed (ON)
		GateImage = "Images\\Menu\\Switch_Closed.jpg";
	}
	else {
		// switch open (OFF) - reuse the toolbar image if an explicit open asset is not available
		// If you have an "Switch_Open.jpg", replace the string below with that path.
		GateImage = "Images\\Menu\\Switch_Opened.jpg";
	}

	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Menu\\XOR3_HI.jpg";
	else
		GateImage = "Images\\Gates\\XOR3.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Menu\\AND3_HI.jpg";
	else
		GateImage = "Images\\Gates\\AND3.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawLed(GraphicsInfo r_GfxInfo, bool selected, bool lit) const
{
    string GateImage;
    if (selected)
    {
        // selected + on/off variations if you want — using a single selected image here
        GateImage = "Images\\Gates\\Led_s.jpg";
    }
    else
    {
        if (lit)
            GateImage = "Images\\Gates\\Led_On.jpg";   // make sure this image exists in your resources
        else
            GateImage = "Images\\Gates\\Led.jpg";
    }

    pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

//TODO: Add similar functions to draw all components







void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected, bool straight) const
{
	//TODO: Add code to draw connection
	color ConnClr = selected ? UI.SelectColor : UI.ConnColor;
	pWind->SetPen(ConnClr, 2);
	int x1 = r_GfxInfo.x1;
	int y1 = r_GfxInfo.y1;
	int x2 = r_GfxInfo.x2;
	int y2 = r_GfxInfo.y2;
	if (straight) {
		pWind->DrawLine(x1, y1, x2, y2);
	}
	else {
		int midX = x1;
		int midY = y2;
		pWind->DrawLine(x1, y1, midX, midY);
		pWind->DrawLine(midX, midY, x2, y2);
	}
}
void Output::DrawComponentLabel(const GraphicsInfo& r_GfxInfo, const string& label) const
{
	if (label.empty()) return;

	// Choose a font size that's readable but small
	pWind->SetFont(18, PLAIN, BY_NAME, "Arial");
	pWind->SetPen(BLACK);


	int gateWidth = UI.AND2_Width;   // default
	int gateHeight = UI.AND2_Height; // default


	int x1 = r_GfxInfo.x1;
	int y1 = r_GfxInfo.y1;


	int approxCharWidth = 7;
	int textWidth = static_cast<int>(label.length()) * approxCharWidth;


	int labelX = x1 + gateWidth / 2 - textWidth / 2;
	int labelY = y1 + gateHeight + 6;

	if (labelX < 2) labelX = 2;

	pWind->DrawString(labelX, labelY, label);
}

Output::~Output()
{
	delete pWind;
}
