#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
	Point Center;
	/*int Height;
	int Width ;
	float Area; /// area can be in CFigure 
	//print ifo shoud print width , height and area
	*/
public:
	CRectangle();
	CRectangle(Point , Point, GfxInfo FigureGfxInfo );

	void CalcCenter();
	/*
	void CalcHeight();
	void CalcWidth();
	*/
	virtual void CalcArea ();

	virtual void Draw(Output* pOut) const;

	virtual void PrintInfo(Output* pOut) const;
	virtual void Save(ofstream &OutFile) const;
	virtual void Load(ifstream &Infile);

	virtual Point TopLeft ()const;
	virtual Point MostLeft() const;
	virtual bool CanMove (Point added , bool up , bool left,Output *pOut) const ;
	virtual void Move(Point added , bool up , bool left);

	virtual bool CanResize (float factor , Output * pOut) ;//checks that the figure can be resized without going out of the window
	virtual void Resize(float factor) ;	//Resize the figure

	virtual bool CheckPointFound(Point P) const;
	CFigure* Copy() const;
	CFigure* Cut() const;

	virtual bool CanRotate(int RotationalAngle, Output* pOut) const;
	virtual void Rotate(int RotationalAngle);
};

#endif