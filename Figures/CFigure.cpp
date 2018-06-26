#include "CFigure.h"

int CFigure::idgenerator=1;

CFigure::CFigure()
{
	FigGfxInfo.BorderWdth=2;
	FigGfxInfo.isFilled=false;
	FigGfxInfo.DrawClr=BLUE;
	Selected=false;
	//ID=??
}

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	ID=idgenerator++;
}

void CFigure::setID(int ID){
	this->ID = ID;
}
bool CFigure::IsFilled() const
{
	return FigGfxInfo.isFilled;
}

color CFigure::getFillColor() const
{
	return FigGfxInfo.FillClr;
}

float CFigure::getArea()
{
	return Area;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

void CFigure::ChngBorderWidth(int width)
{
	FigGfxInfo.BorderWdth = width;
}
int CFigure::getBorderWidth()
{
	return FigGfxInfo.BorderWdth;
}
void CFigure::del_from_string(string &str,int x)///utility fuction ... called in load function only
{
	
	string s=to_string(x);
	int idx=str.find(s);
	if (idx!=-1)
		str.erase(idx,s.size());
}

