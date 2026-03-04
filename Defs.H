#ifndef CONST_H
#define CONST_H

//This header file contains some defenitions to be used all over the application
#define EDIT_Label_ID 100
//All possible actions
enum ActionType
{
	ADD_Buff,			//Add 1-input Buffer gate
	ADD_INV,			//Add 1-input Inverter gate
	ADD_AND_GATE_2,		//Add 2-input AND gate
	ADD_OR_GATE_2,		//Add 2-input OR gate
	ADD_NAND_GATE_2,	//Add 2-input NAND gate
	ADD_NOR_GATE_2,		//Add 2-input NOR gate
	ADD_XOR_GATE_2,		//Add 2-input XOR gate
	ADD_XNOR_GATE_2,	//Add 2-input XNOR gate
	ADD_AND_GATE_3,		//Add 3-input AND gate
	ADD_NOR_GATE_3,		//Add 3-input NOR gate
	ADD_XOR_GATE_3,		//Add 3-input XOR gate
	ADD_Switch,			//Add Switch
	ADD_LED,			//Add LED
	ADD_CONNECTION,		//Add Wire Connection

	ADD_Label,			//Add Label to a Component, a Connection
	EDIT_Label,			//Edit Label of a Component, a Connection

	Create_TruthTable,	//Create Truth Table of the Circuit

	Change_Switch,		//Change Switch Status in Simulation Mode

	SELECT,		//Select a Component, a Connection
	DEL,		//Delete a Component, a Connection
	MOVE,		//Move a Component, a Connection

	SAVE,		//Save the whole Circuit to a file
	LOAD,		//Load a Circuit from a file

	UNDO,		//Undo the last Action preformed
	REDO,		//Redo the last Action canceled
	COPY,

	CUT,
	PASTE,
	MULTI_SELECT,



	DSN_MODE,	//Switch to Design mode
	SIM_MODE,	//Switch to Simulatiom mode

	EXIT,		//Exit the application
	Add_vildation,
	Add_operation,
	Add_probing,

	STATUS_BAR,		//A click on the status bar
	DSN_TOOL,	//A click on an empty place in the design tool bar

};

//Possible Status for the pin
enum STATUS
{
	LOW,
	HIGH
};

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};


enum DsgnMenuItem //The items of the design menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_AND2,		//AND gate item in menu
	ITM_AND3,       //AND3 gate item in menu
	ITM_NAND2,      //NAND gate item in menu
	ITM_OR2,		//OR gate item in menu
	ITM_NOR2,       //NOR gate item in menu
	ITM_NOR3,       //NOR3 gate item in menu
	ITM_XOR2,       //XOR gate item in menu
	ITM_XOR3,       //XOR3 gate item in menu
	ITM_XNOR2,      //XNOR gate item in menu
	ITM_BUFF,       //Buffer gate item in menu
	ITM_INV,        //Inverter gate item in menu
	ITM_LED,       //LED item in menu
	ITM_CONNECTION, //Connection item in menu
	ITM_LABEL,      //Label item in menu
	ITM_EDIT_LABEL,  //Edit Label item in menu
	ITM_SELECT,     //Select item in menu
	ITM_DELETE,     //Delete item in menu
	ITM_MOVE,       //Move item in menu
	ITM_SAVE,       //Save item in menu
	ITM_LOAD,       //Load item in menu
	ITM_COPY,        //Copy item in menu
	ITM_CUT,         //Cut item in menu
	ITM_PASTE,       //Paste item in menu
	ITM_MULTI_SELECT, //Multi-Select item in menu
	ITM_UNDO,        //Undo item in menu
	ITM_REDO,        //Redo item in menu
	ITM_SWITCH_TO_SIM, //Switch to Simulation mode item in menu
	ITM_SWITCH,    //Switch item in menu
	ITM_EXIT,		//Exit item


	//TODO: Add more items names here

	ITM_DSN_CNT		//no. of design menu items ==> This should be the last line in this enum

};


enum SimMenuItem //The items of the simulation menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	/*ITM_SIM,*/	//Simulate menu item
	ITM_VALIDATION,	//Circuit Validation menu item 
	ITM_OPERATION, //Simulate Circuit Operation menu item
	ITM_TRUTH,	//Truth table menu item
	ITM_PROBING, //Probing menu item
	ITM_DESIGN,	//Switch To Design menu item

	//TODO:Add more items names here


	ITM_SIM_CNT		//no. of simulation menu items ==> This should be the last line in this enum

};

//Maximum number of input pins that can be connected to any output pin
#define MAX_CONNS 20

//assume fan out is 5 for now it can be read from the user or can be predefined as const
enum FANOUT
{
	AND2_FANOUT = 5,	//Default fan out of 2-input AND gate
	OR2_FANOUT = 5,	//Default fan out of 2-input AND gate
	NAND2_FANOUT = 5,	//Default fan out of 2-input AND gate
	NOR2_FANOUT = 5,	//Default fan out of 2-input AND gate
	XOR2_FANOUT = 5,	//Default fan out of 2-input AND gate
};


//A structure to contain drawing parameters for each component
//Each component occupies a rectangluar area so it needs 2 points to represent that area
//this structure can be extended if desired
struct GraphicsInfo
{
	int x1, y1, x2, y2;
};

#ifndef NULL
#define NULL 0
#endif

#endif