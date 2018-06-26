#include "Output.h"

Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;

	UI.width = 1330;
	UI.height = 700;
	UI.wx = 5;
	UI.wy =5;


	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 50;
	UI.ColorSubMenuHeight = 300;
	UI.SubMenuItemWidth = 300;
	UI.SubMenuItemHeight = 77;

	//UI.PopImageHeight=305;//////
	//UI.PopImageWidth=305;///////

	setCrntDrawColor(BLUE);	//Drawing color
	setCrntFillColor(GREEN);	//Filling color
	UI.MsgColor = line;		//Messages color
	UI.BkGrndColor = background;	//Background color
	UI.HighlightColor = BLACK;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = status;
	setCrntPenWidth(2);	//width of the figures frames
	zoom_factor=1;
	zoom_center.x=0;   zoom_center.y=0;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");

	FillUIArrays();
	CreateDrawToolBar();
	//CreatePlayToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

void Output::FillUIArrays() const {

	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem

	//fill menu item images
	UI.MenuItemImages[ITM_LINE] = "images\\MenuItems\\line.jpg";
	UI.MenuItemImages[ITM_RECT] = "images\\MenuItems\\Menu_Rect.jpg";
	UI.MenuItemImages[ITM_TRI] = "images\\MenuItems\\Menu_tri.jpg";
	UI.MenuItemImages[ITM_CIRC] = "images\\MenuItems\\Menu_Circ.jpg";
	UI.MenuItemImages[ITM_CHNG_DRAW_CLR] = "images\\MenuItems\\Menu_Change.jpg";
	UI.MenuItemImages[ITM_CHNG_FILL_CLR]= "images\\MenuItems\\Menu_Fill.jpg";
	UI.MenuItemImages[ITM_CHNG_BK_CLR]= "images\\MenuItems\\Menu_Background.jpg";
	UI.MenuItemImages[ITM_BORD_DRAW_WID]= "images\\MenuItems\\border.jpg";
	UI.MenuItemImages[ITM_SELECT]= "images\\MenuItems\\Select.jpg";
	UI.MenuItemImages[ITM_DEL]= "images\\MenuItems\\Broom.jpg";
	UI.MenuItemImages[ITM_MOVE]= "images\\MenuItems\\move.jpg";
	UI.MenuItemImages[ITM_RESIZE]= "images\\MenuItems\\Resize.jpg";
	UI.MenuItemImages[ITM_ROTATE]= "images\\MenuItems\\Rotate.jpg";
	UI.MenuItemImages[ITM_ZOOM_IN]= "images\\MenuItems\\zoom-plus.jpg";
	UI.MenuItemImages[ITM_ZOOM_OUT]= "images\\MenuItems\\zoom-minus.jpg";
	UI.MenuItemImages[ITM_CPY]= "images\\MenuItems\\cpy.jpg";
	UI.MenuItemImages[ITM_CUT]= "images\\MenuItems\\cut.jpg";
	UI.MenuItemImages[ITM_PASTE]= "images\\MenuItems\\Menu_Paste.jpg";
	UI.MenuItemImages[ITM_SND_BK]= "images\\MenuItems\\Menu_Bringback.jpg";
	UI.MenuItemImages[ITM_BRNG_FR]= "images\\MenuItems\\Menu_BringFront.jpg";
	UI.MenuItemImages[ITM_SAVE]= "images\\MenuItems\\Save.jpg";
	UI.MenuItemImages[ITM_LOAD]= "images\\MenuItems\\Load.jpg";
	UI.MenuItemImages[ITM_TO_PLAY]= "images\\MenuItems\\Menu_Play.jpg";
	UI.MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";

	//fill play item images
	UI.PlayItemImages[PLAY_ITM_PICK]="images\\MenuItems\\pick_hide.jpg";
	UI.PlayItemImages[PLAY_ITM_SCRAMBLE]="images\\MenuItems\\find.jpg";
	UI.PlayItemImages[PLAY_ITM_TO_DRAW]="images\\MenuItems\\Draw_mode.jpg";
	
	//fill zoom item images
	UI.ZoomItemImages[ITM_LINE] = "images\\MenuItems\\line_blur.jpg";
	UI.ZoomItemImages[ITM_RECT] = "images\\MenuItems\\Menu_Rect_blur.jpg";
	UI.ZoomItemImages[ITM_TRI] = "images\\MenuItems\\Menu_tri_blur.jpg";
	UI.ZoomItemImages[ITM_CIRC] = "images\\MenuItems\\Menu_Circ_blur.jpg";
	UI.ZoomItemImages[ITM_CHNG_DRAW_CLR] = "images\\MenuItems\\Menu_Change.jpg";
	UI.ZoomItemImages[ITM_CHNG_FILL_CLR]= "images\\MenuItems\\Menu_Fill.jpg";
	UI.ZoomItemImages[ITM_CHNG_BK_CLR]= "images\\MenuItems\\Menu_Background.jpg";
	UI.ZoomItemImages[ITM_BORD_DRAW_WID]= "images\\MenuItems\\border_blur.jpg";
	UI.ZoomItemImages[ITM_SELECT]= "images\\MenuItems\\Select.jpg";
	UI.ZoomItemImages[ITM_DEL]= "images\\MenuItems\\Broom.jpg";
	UI.ZoomItemImages[ITM_MOVE]= "images\\MenuItems\\move_blur.jpg";
	UI.ZoomItemImages[ITM_RESIZE]= "images\\MenuItems\\Resize_blur.jpg";
	UI.ZoomItemImages[ITM_ROTATE]= "images\\MenuItems\\Rotate_blur.jpg";
	UI.ZoomItemImages[ITM_ZOOM_IN]= "images\\MenuItems\\zoom-plus.jpg";
	UI.ZoomItemImages[ITM_ZOOM_OUT]= "images\\MenuItems\\zoom-minus.jpg";
	UI.ZoomItemImages[ITM_CPY]= "images\\MenuItems\\cpy_blur.jpg";
	UI.ZoomItemImages[ITM_CUT]= "images\\MenuItems\\cut_blur.jpg";
	UI.ZoomItemImages[ITM_PASTE]= "images\\MenuItems\\Menu_Paste_blur.jpg";
	UI.ZoomItemImages[ITM_SND_BK]= "images\\MenuItems\\Menu_Bringback_blur.jpg";
	UI.ZoomItemImages[ITM_BRNG_FR]= "images\\MenuItems\\Menu_BringFront_blur.jpg";
	UI.ZoomItemImages[ITM_SAVE]= "images\\MenuItems\\Save.jpg";
	UI.ZoomItemImages[ITM_LOAD]= "images\\MenuItems\\Load.jpg";
	UI.ZoomItemImages[ITM_TO_PLAY]= "images\\MenuItems\\Menu_Play_blur.jpg";
	UI.ZoomItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";

}
/////////////////////////////////////////////////////////////////////////////////////////

bool Output::Check_Point(Point P1) const 
{
	bool valid = (P1.y >= UI.ToolBarHeight) && (P1.y <= UI.height-UI.StatusBarHeight) &&(P1.x <= UI.width-16) &&(P1.x >= 0); /// -16 3shan feh 7aga f el window 
	return valid;
}


/////////////////////////////////////////////////////////////////////////////////////////
window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);  // fill color
	pW->SetPen(UI.BkGrndColor, 1); //frame of window
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	//draw window
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreateDrawToolBar() const
{
	ClearToolBar();
	UI.InterfaceMode = MODE_DRAW;


	//Draw menu item one image at a time
	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(UI.MenuItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(line, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateBorder()
{
	pWind->SetPen(line, 3);
	pWind->DrawLine((UI.width+1)/2+16, UI.ToolBarHeight, (UI.width+1)/2+16, UI.height-UI.StatusBarHeight); // 16 : bec of the used library
}
void Output::CreatePlayToolBar() const
{
	ClearToolBar();
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu

	for(int i=0; i<PLAY_ITM_COUNT; i++)
		pWind->DrawImage(UI.PlayItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);

	pWind->SetPen(line, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateZoomToolBar() const
{
	ClearToolBar();
	UI.InterfaceMode = MODE_DRAW;

	for(int i=0; i<DRAW_ITM_COUNT; i++)
		pWind->DrawImage(UI.ZoomItemImages[i], i*UI.MenuItemWidth,0,UI.MenuItemWidth, UI.ToolBarHeight);

	pWind->SetPen(line, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
/////////////////////////
void Output::CreateColorSubMenu() const
{

	string ColorItem = "images\\ColorItem\\Color1.jpg";
	pWind->DrawImage(ColorItem,0,UI.ToolBarHeight,UI.SubMenuItemWidth, UI.ColorSubMenuHeight);
}
////////////////////////////////////////////////////////////////////////////////////////

void Output::CreateBorderWidthSubMenu() const
{

	string BorderItem = "images\\BorderWidthItem\\BorderWidth.jpg";
	pWind->DrawImage(BorderItem,0,UI.ToolBarHeight,UI.SubMenuItemWidth, UI.SubMenuItemHeight*BORDER_ITM_COUNT);
	
}
////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateRotationAngleSubMenu() const
{
	
	string RotationItem = "images\\RotationItem\\Rotation.jpg";
	pWind->DrawImage(RotationItem,0,UI.ToolBarHeight,UI.SubMenuItemWidth, UI.SubMenuItemHeight*	ROTATION_ITM_COUNT);
}
////////////////////////////////////////////////////////////////////////////////////////

void Output:: CreateResizeSubMenu() const
{
	string ResizeBar= "images\\PopImages\\Resize.jpg";
	pWind->DrawImage(ResizeBar,0 ,UI.ToolBarHeight ,UI.SubMenuItemWidth, UI.SubMenuItemHeight*RESIZE_ITM_COUNT);
}

/////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);

}
///////////////////////////////////////////////////////////////////////////////////////

void Output::ClearToolBar() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output:: CreatePickAndHideSubMenu() const
{
	string PickSubMenu = "images\\PickandHide\\Pick.jpg";
	pWind->DrawImage (PickSubMenu,0,UI.ToolBarHeight , UI.SubMenuItemWidth, UI.SubMenuItemHeight* PICK_ITM_COUNT);

}

/////////////////////////////////////////////////////////////////////////////////////
void Output::setZoomMode(bool zoom){
	
	zoom_mode = zoom;
}
///////////////////////////////////////////////////////////////////////////////////
bool Output::getZoomMode(){
	return zoom_mode;
}
///////////////////////////////////////////////////////////////////////////////////
void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight/1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drwawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
color Output:: getBackGroundColor() const
{
	return UI.BkGrndColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int Output::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}
/////////////////////////////////////////////////////////////////////////////////////////
GUI_MODE Output:: get_Mode()const
{
	return UI.InterfaceMode;
}
/////////////////////////////////////////////////////////////////////////
color Output::getHighlightedColor() const{
	return UI.HighlightColor;
}
/////////////////////////////////////////////////////////////////////////////////
void Output::set_zoom_factor(float f)
{
	zoom_factor *= f ;
}
/////////////////////////////////////////////////////////////////////////
void Output::set_zoom_center( Point P)
{
	zoom_center.x = P.x ;
	zoom_center.y = P.y ;
}
//////////////////////////////////////////////////////////////////
float Output::get_zoom_factor()
{
	return zoom_factor;
}
////////////////////////////////////////////////////////////////////
Point Output::get_zoom_center()
{
	return zoom_center;
}
/////////////////////////////////////////////////////////////////
int Output::getUIWidth() const{
	return UI.width;
}
///////////////////////////////////////////////////////////////
int Output::getUIHeight() const{
	return UI.height;
}
/////////////////////////////////////////////////////
int Output::getUIStatusbarHeight() const{
	return UI.StatusBarHeight;
}
/////////////////////////////////////////////////
int Output:: getUIToolbarHeight() const{
	return UI.ToolBarHeight;
}
////////////////////////////////////////////////////
void Output::setCrntDrawColor(color usercolor){
	UI.DrawColor = usercolor;
}
/////////////////////////////////////////////////////
void Output::setCrntFillColor(color usercolor){
	UI.FillColor = usercolor;
}
//////////////////////////////////////////////////////
void Output::setCrntPenWidth(int userpenwidth){
	UI.PenWidth = userpenwidth;
}
/////////////////////////////////////////////////////
void Output::setCrntBKGrndColor(color usercolor){
	UI.BkGrndColor = usercolor;
}
/////////////////////////////////////////////////////////

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//



//////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = LineGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, LineGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	style = FRAME;


	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y, style);

}

///////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else	
		style = FRAME;


	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

}

///////////////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawTria(Point P1, Point P2,Point P3, GfxInfo TriangleGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; 
	else			
		DrawingClr = TriangleGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, TriangleGfxInfo.BorderWdth);

	drawstyle style;
	if (TriangleGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(TriangleGfxInfo.FillClr);
	}
	else	
		style = FRAME;


	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y,P3.x,P3.y, style);

}

////////////////////////////////////////////////////////////////////////////////////////////

void Output::DrawCirc(Point P1, int Radius, GfxInfo CircGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)	
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else			
		DrawingClr = CircGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, CircGfxInfo.BorderWdth);	//Set Drawing color & width

	drawstyle style;
	if (CircGfxInfo.isFilled)	
	{
		style = FILLED;		
		pWind->SetBrush(CircGfxInfo.FillClr);
	}
	else	
		style = FRAME;
	pWind->DrawCircle(P1.x, P1.y, Radius, style);

}

/////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

