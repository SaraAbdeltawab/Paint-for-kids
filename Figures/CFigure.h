#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\Output.h"
#include <fstream> ////// deh bardo makanha hna ?
#include <cmath>


//Base class for all figures
class CFigure
{
protected:
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	float Area;

	static int idgenerator;
	void del_from_string(string &str,int x);///utility fuction ... called in load function only///
	
public:
	CFigure();
	CFigure(GfxInfo FigureGfxInfo);
	void setID(int ID);
	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const; //check whether fig is selected
	bool IsFilled()const;
	color getFillColor() const;	
	virtual Point MostLeft() const = 0;
	virtual Point TopLeft() const = 0; // gets the top left point in the figure
	virtual void Draw(Output* pOut) const  =  0; //Draw the figure

	virtual void CalcArea () = 0;
	float getArea();


	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	virtual void ChngFillClr(color Fclr);	//changes the figure's filling color
	void ChngBorderWidth(int width); //changes the figure's BorderWidth
	int getBorderWidth();
	virtual bool CheckPointFound(Point P) const =0 ; //Check if the given point is inside the figure or not  //pure virtual
	virtual CFigure* Copy() const = 0; 
	virtual CFigure* Cut() const = 0; 

	virtual bool CanRotate(int RotationalAngle, Output* pOut) const = 0; //Check if the figure can be rotated without going out of the window or not
	virtual void Rotate(int RotationAngle) = 0;		//Rotate the figure
 
	virtual bool CanMove (Point added , bool up , bool left,Output *pOut) const =0; /// checks that the figure can move to its destination without going out of the window
	virtual void Move(Point added , bool up , bool left) = 0;		//Move the figure

	virtual bool CanResize (float factor , Output * pOut) =0;//checks that the figure can be resized without going out of the window
	virtual void Resize(float factor) = 0;	//Resize the figure


	virtual void Save(ofstream &OutFile) const = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file

	virtual void PrintInfo(Output* pOut) const = 0;	//print all figure info on the status bar
};

#endif