#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
	void FillUIArrays() const; //fill MenuItemImages array, ColorArr
	float zoom_factor;
	Point zoom_center;
	bool zoom_mode;

public:
	Output();		

	window* CreateWind(int, int, int , int) const; //creates the application window
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateZoomToolBar() const; //creates Draw tool bar while zooming
	void CreateColorSubMenu() const; //create color submenu


	
	void CreateStatusBar() const;	//create the status bar

	void CreateResizeSubMenu() const; ///creates resize submenu
	void CreateBorderWidthSubMenu() const;
	void CreateRotationAngleSubMenu() const;
	void CreatePickAndHideSubMenu() const;

	bool Check_Point(Point P1) const;

	Input* CreateInput() const; //creates a pointer to the Input object	
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	void ClearToolBar() const;
	void CreateBorder(); //In Scramble and Find border between left figures and right figures 

	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected = false) const;  //Draw a rectangle 
	void DrawLine(Point P1, Point P2, GfxInfo LineGfxInfo, bool selected = false) const;
	void DrawTria(Point P1, Point P2,Point p3, GfxInfo TriangleGfxInfo, bool selected = false) const;
	void DrawCirc(Point P1, int Radius, GfxInfo CircGfxInfo, bool selected = false) const;

	void PrintMessage(string msg) const;	//Print a message on Status bar

	color getCrntDrawColor() const;	//get current drwawing color  ///don't use UI outside the output ////!!!!// NOTE
	color getCrntFillColor() const;	//get current filling color
	color getBackGroundColor() const;
	color getHighlightedColor() const;
	int getCrntPenWidth() const; //get current pen width
	int getUIWidth() const;
	int getUIHeight() const;
	int getUIStatusbarHeight() const;
	int getUIToolbarHeight() const;
	float get_zoom_factor();
	Point get_zoom_center();
	GUI_MODE get_Mode()const;

	void set_zoom_factor(float);
	void set_zoom_center (Point );

	void setCrntDrawColor(color usercolor);
	void setCrntFillColor(color usercolor);
	void setCrntBKGrndColor(color usercolor);
	void setCrntPenWidth(int userpenwidth);

	bool getZoomMode();
	void setZoomMode(bool zoom);
	~Output();
};

#endif