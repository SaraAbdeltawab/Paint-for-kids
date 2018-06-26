#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CFigure.h"

class CTriangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
	Point Corner3;
	Point Center;
public:
	CTriangle();
	CTriangle(Point P1 , Point P2,Point P3, GfxInfo FigureGfxInfo );
	virtual void Draw(Output* pOut) const;
	void CalcCenter();
	virtual void CalcArea ();

	virtual void PrintInfo(Output* pOut) const;
	virtual void Save(ofstream &OutFile) const;
	virtual void Load(ifstream &Infile);

	virtual Point TopLeft()const;
	virtual Point MostLeft() const;
	virtual bool CanMove (Point added , bool up , bool left,Output *pOut) const ;
	virtual void Move(Point added , bool up , bool left);

	virtual bool CanResize (float factor , Output * pOut);//checks that the figure can be resized without going out of the window
	virtual void Resize(float factor) ;	//Resize the figure

	virtual bool CheckPointFound(Point P) const;
	virtual CFigure* Copy() const;
	CFigure* Cut() const;

	virtual bool CanRotate(int RotationalAngle, Output* pOut) const;
	virtual void Rotate(int RotationalAngle);
};

#endif