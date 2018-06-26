#ifndef INPUT_H
#define INPUT_H

#include "..\DEFS.h"
#include "UI_Info.h" 
#include "..\CMUgraphicsLib\CMUgraphics.h"

class Output;
class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window
public:
	Input(window *pW);		//Consturctor
	void GetPointClicked(int &x, int &y) const;//Get coordinate where user clicks
	string GetSrting(Output* pO) const ;	 //Returns a string entered by the user

	ActionType GetUserAction() const; //Read the user click and map to an action
	ActionType GetUserAction(int x, int y) const; // map a click to an action
	color GetUserColor() const; //Read the user click and map to a color

	BorderWidthAction GetUserBorderWidth() const; //Read the user click and map to a borderwidth
	RotationAction GetUserRotationAngle() const; //Read the user click and map to a rotational angle
	ResizeFactor GetUserResizeFactor()const;

	PickChoices GetUserPickChoice() const;

	bool CheckPointOnSelectIcon(Point Click) const; //For select action to stop selection

	~Input();
};

#endif