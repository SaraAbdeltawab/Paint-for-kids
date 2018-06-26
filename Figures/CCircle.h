#ifndef CCIRCLE_H
#define CCIRCLE_H

#include "CFigure.h"

class CCircle : public CFigure
{
private:

	Point Center;	
	int Radius;
public:

	CCircle();
	CCircle(Point P1 , int R, GfxInfo FigureGfxInfo );
	virtual void Draw(Output* pOut) const;

	virtual void PrintInfo(Output* pOut) const;
	virtual void Save(ofstream &OutFile) const;
	virtual void Load(ifstream &Infile);

	virtual Point TopLeft ()const;
	virtual Point MostLeft() const;
	virtual void CalcArea ();

	virtual bool CanMove (Point added , bool up , bool left,Output *pOut) const ;
	virtual void Move(Point added , bool up , bool left);

	virtual bool CanResize (float factor , Output * pOut);//checks that the figure can be resized without going out of the window
	virtual void Resize(float factor) ;	//Resize the figure

	virtual bool CheckPointFound(Point P) const;
	CFigure* Copy() const;
	CFigure* Cut() const;

	virtual bool CanRotate(int RotationalAngle, Output* pOut) const;
	virtual void Rotate(int RotationalAngle);
};

#endif

