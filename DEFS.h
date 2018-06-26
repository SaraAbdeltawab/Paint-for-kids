#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contais some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	DRAW_LINE,		//Draw Line
	DRAW_RECT,		//Draw Rectangle
	DRAW_TRI,		//Draw Triangle
	DRAW_CIRC,		//Draw Circle
	CHNG_DRAW_CLR,	//Change the drawing color
	CHNG_FILL_CLR,	//Change the filling color
	CHNG_BK_CLR,	//Change background color
	BRD_DRAW_WID,   //Changing border drawing width
	SELECT,         //To select one or more figure
	DEL,			//Delete a figure(s)
	MOVE,			//Move a figure(s)
	RESIZE,			//Resize a figure(s)
	ROTATE,			//Rotate a figure(s)
	ZOOM_IN,        //to zoom in
	ZOOM_OUT,       //to zoom out
	COPY,     
	CUT,
	PASTE,
	SEND_BACK,		//Send a figure to the back of all figures
	BRNG_FRNT,		//Bring a figure to the front of all figures
	SAVE,			//Save the whole graph to a file
	LOAD,			//Load a graph from a file
	EXIT,			//Exit the application

	DRAWING_AREA,	//A click on the drawing area
	STATUS,			//A click on the status bar
	EMPTY,			//A click on empty place in the toolbar

	TO_DRAW,		//Switch interface to Draw mode
	
	PICK_AND_HIDE,
	SCRAMBLE_AND_FIND,
	TO_PLAY		//Switch interface to Play mode
};

enum BorderWidthAction{

	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	CLOSE_BORDERWIDTH,
	EMPTY_BORDERWIDTH
};

enum RotationAction{

	NINTY,
	ONEEIGHTY,
	TWOSEVENTY,
	CLOSE_ROTATION,
	EMPTY_ROTATION
};

enum ResizeFactor{
	QUARTER,
	HALF,
	BYTWO,
	BYFOUR,
	CLOSE_RESIZE,
	EMPTY_RESIZE
};

enum PickChoices{
	TYPE,
	FILL_COLOR,
	TYPE_AND_FILL_COLOR,
	AREA,
	CLOSE_PICK,
	EMPTY_PICK
};

struct Point	//To be used for figures points
{ int x,y; };


struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};

#endif