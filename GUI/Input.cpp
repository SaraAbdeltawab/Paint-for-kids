#include "Input.h"
#include "Output.h"


Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if(Key == 8 )	//BackSpace is pressed
		{
			if (Label.size()==0)
				continue;
			Label.resize(Label.size() -1 );	
		}
		else
			Label+= Key;
		pO->PrintMessage(Label);
	}
}

ActionType Input::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	return GetUserAction(x,y);
}

ActionType Input::GetUserAction(int x, int y) const
{

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode  
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check which Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{

			case ITM_LINE: return DRAW_LINE;
			case ITM_RECT: return DRAW_RECT;
			case ITM_TRI: return DRAW_TRI;
			case ITM_CIRC: return DRAW_CIRC;		
			case ITM_CHNG_DRAW_CLR: return CHNG_DRAW_CLR;
			case ITM_CHNG_FILL_CLR: return CHNG_FILL_CLR;
			case ITM_CHNG_BK_CLR: return CHNG_BK_CLR;
			case ITM_BORD_DRAW_WID: return BRD_DRAW_WID;
			case ITM_SELECT: return SELECT;
			case ITM_DEL: return DEL;
			case ITM_MOVE: return MOVE;
			case ITM_RESIZE: return RESIZE;
			case ITM_ROTATE: return ROTATE;
			case ITM_ZOOM_IN: return ZOOM_IN;
			case ITM_ZOOM_OUT: return ZOOM_OUT;
			case ITM_CPY: return COPY;
			case ITM_CUT: return CUT;
			case ITM_PASTE: return PASTE;
			case ITM_SND_BK: return SEND_BACK;
			case ITM_BRNG_FR: return BRNG_FRNT;
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_TO_PLAY: return TO_PLAY;
			case ITM_EXIT: return EXIT;	

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}


		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode     
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{

			case PLAY_ITM_PICK: return PICK_AND_HIDE;
			case PLAY_ITM_SCRAMBLE: return SCRAMBLE_AND_FIND;
			case PLAY_ITM_TO_DRAW: return TO_DRAW;
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}	

		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}

		//[3] User clicks on the status bar
		return STATUS;

	}

}

bool Input::CheckPointOnSelectIcon(Point Click) const{

	ActionType ActType = GetUserAction(Click.x, Click.y);
	if(ActType == SELECT) return true;
	return false;
}

//This function reads the position where the user clicks to determine the desired color
color Input::GetUserColor() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	//[1] If user clicks on the Toolbar
	//check in color bar
	if(y <= UI.ColorSubMenuHeight+UI.ToolBarHeight && y >= UI.ToolBarHeight && x <= UI.SubMenuItemWidth){
		return pWind->GetColor(x,y);
	}

	return UI.HighlightColor;

}

BorderWidthAction Input::GetUserBorderWidth() const
{
	int x,y;
	GetPointClicked(x,y);  //Get the coordinates of the user click


	//If user clicks on the BorderWidth submenu

	if ( x >= 0 && x < UI.SubMenuItemWidth && y >UI.ToolBarHeight)
	{	
		//Check which Submenu item was clicked
		//==> This assumes that menu items are lined up verically <==
		int ClickedItemOrder = ((y - UI.ToolBarHeight)/ UI.SubMenuItemHeight);

		switch (ClickedItemOrder)
		{
		case ITM_TWO: return TWO;
		case ITM_THREE: return THREE;
		case ITM_FOUR: return FOUR;
		case ITM_SIX: return SIX;
		case ITM_FIVE: return FIVE;
		case ITM_CLOSE_BORDERWIDTH: return CLOSE_BORDERWIDTH;

		default: return EMPTY_BORDERWIDTH;
		}
	}
	return EMPTY_BORDERWIDTH;
}


RotationAction Input::GetUserRotationAngle() const
{
	int x,y;
	GetPointClicked(x,y);  //Get the coordinates of the user click


	//If user clicks on the Rotation submenu

	if ( x >= 0 && x < UI.SubMenuItemWidth && y >UI.ToolBarHeight)
	{	
		//Check which Submenu item was clicked
		//==> This assumes that menu items are lined up verically <==
		int ClickedItemOrder = ((y - UI.ToolBarHeight)/ UI.SubMenuItemHeight);

		switch (ClickedItemOrder)
		{
		case ITM_NINTY: return NINTY;
		case ITM_ONEEIGHTY: return ONEEIGHTY;
		case ITM_TWOSEVENTY: return TWOSEVENTY;
		case ITM_CLOSE_ROTATION: return CLOSE_ROTATION;

		default: return EMPTY_ROTATION;
		}
	}
	return EMPTY_ROTATION;
}

ResizeFactor Input:: GetUserResizeFactor()const
{
	int x,y;
	GetPointClicked(x,y);

	if ( x >= 0 && x < UI.SubMenuItemWidth && y >UI.ToolBarHeight)
	{
		int ClickedItemOrder = ((y - UI.ToolBarHeight)/ UI.SubMenuItemHeight);

		switch (ClickedItemOrder)
		{
		case ITM_QUARTER: return QUARTER;
		case ITM_HALF: return HALF;
		case ITM_BYTWO: return BYTWO;
		case ITM_BYFOUR: return BYFOUR;
		case ITM_CLOSE_RESIZE: return CLOSE_RESIZE;

		default: return EMPTY_RESIZE;
		}
	}
	return EMPTY_RESIZE;
}

PickChoices Input:: GetUserPickChoice() const
{
	int x,y;
	GetPointClicked(x,y);

	if ( x >= 0 && x < UI.SubMenuItemWidth && y >UI.ToolBarHeight)
	{
		int ClickedItemOrder = ((y - UI.ToolBarHeight)/ UI.SubMenuItemHeight);

		switch (ClickedItemOrder)
		{
		case ITM_TYPE: return TYPE;
		case ITM_FILL_COLOR: return FILL_COLOR;
		case ITM_TYPE_AND_FILL_COLOR: return TYPE_AND_FILL_COLOR;
		case ITM_AREA : return AREA;
		case ITM_CLOSE_PICK: return CLOSE_PICK;

		default: return EMPTY_PICK;
		}
	}
	return EMPTY_PICK;

}
Input::~Input()
{
}
