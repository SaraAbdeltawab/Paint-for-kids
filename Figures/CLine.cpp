#include "CLine.h"
#include <math.h> //mkano hna sa7 ??? // sara //e7na hn2ld b3d b2a //hagar XD


CLine::CLine () ///defualt constructor for load action
{
	/// any values
	point1.x=150;
	point1.y=150;
	point2.x=200;
	point2.y=200;
	CalcCenter();
	CalcArea();
}

CLine::CLine(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	point1 = P1;
	point2 = P2;
	CalcCenter();
	CalcArea();
}
void CLine:: ChngFillClr(color Fclr)
{
	FigGfxInfo.isFilled = false;  /// we don't change the fill color of the line as it is never filled 
}
void CLine:: CalcCenter()
{
	Center.x = (point1.x + point2.x)/ 2;
	Center.y = (point1.y + point2.y)/2;
}

void CLine::CalcArea()
{
	Area =(float) sqrt(pow(point1.x-point2.x,2) +pow(point1.y-point2.y,2));
}
void CLine::Draw(Output* pOut) const
{
	//Call Output::DrawLine to draw a line on the screen	
	float f=pOut->get_zoom_factor();
	Point C = pOut->get_zoom_center();
	Point P1,P2 ;
	P1.x=(int)(f*(point1.x -C.x)+C.x) ; P1.y=(int)(f*(point1.y -C.y)+C.y);
	P2.x=(int)(f*(point2.x -C.x)+C.x) ; P2.y=(int)(f*(point2.y -C.y)+C.y);
	pOut->DrawLine(P1 ,P2, FigGfxInfo, Selected) ;
	
}

Point CLine::MostLeft() const{
	return (point1.x < point2.x)? point1 : point2;
}

void CLine:: PrintInfo(Output* pOut) const
{
	string str="Line: ID = "+to_string(ID);
	str+=" start point ("+to_string(point1.x)+","+to_string(point1.y)+") , end point("+to_string(point2.x)+","+to_string(point2.y)+")";
	str+=" color = red:"+to_string(FigGfxInfo.DrawClr.ucRed)+" green:"+to_string(FigGfxInfo.DrawClr.ucGreen)+" blue:"+to_string(FigGfxInfo.DrawClr.ucBlue);
	float cmArea = (float)(Area/37.79);
	str+=" Area = "+to_string(cmArea);
	pOut->PrintMessage(str);
}

void CLine::Save(ofstream &OutFile) const
{
	/// The line is type 0
	OutFile<<0<<"  "<<ID<<"  "<<point1.x<<"  "<<point1.y<<"  "<<point2.x<<"  "<<point2.y<<"  "<<FigGfxInfo.BorderWdth<<" ";

	string drwclr=to_string(FigGfxInfo.DrawClr.ucRed)+"  "+to_string(FigGfxInfo.DrawClr.ucGreen)+"  "+to_string(FigGfxInfo.DrawClr.ucBlue)+"  ";

	OutFile<<drwclr<<endl;
}

void CLine::Load(ifstream &Infile)
{
	Infile>>ID>>point1.x>>point1.y>>point2.x>>point2.y>>FigGfxInfo.BorderWdth;
	if (idgenerator<=ID)
		idgenerator=ID+1;
	int r,g,b;
	Infile>>r>>g>>b;
	color drw(r,g,b);
	FigGfxInfo.DrawClr=drw;
	FigGfxInfo.isFilled=false;

	CalcCenter();
	CalcArea();

}

Point CLine:: TopLeft() const
{
	if (point1.y<point2.y)
		return point1;
	else if (point2.y<point1.y)
		return point2;
	else //==
		if (point1.x<point2.x)
			return point1;
		else
			return point2;
}

bool CLine::CanMove (Point added , bool up , bool left,Output *pOut) const
{
	Point P1=point1;
	Point P2=point2;
	if (up)
	{
		P1.y-=added.y;
		P2.y-=added.y;
	}
	else
	{
		P1.y+=added.y;
		P2.y+=added.y;
	}
	if (left)
	{
		P1.x-=added.x;
		P2.x-=added.x;
	}
	else
	{
		P1.x+=added.x;
		P2.x+=added.x;
	}
	return (pOut->Check_Point(P1)&&pOut->Check_Point(P2)); // Check that the figure won't get out of the window
}

void CLine::Move(Point added , bool up , bool left)
{
	if (up)
	{
		point1.y-=added.y;
		point2.y-=added.y;
	}
	else
	{
		point1.y+=added.y;
		point2.y+=added.y;
	}
	if (left)
	{
		point1.x-=added.x;
		point2.x-=added.x;
	}
	else
	{
		point1.x+=added.x;
		point2.x+=added.x;
	}

	CalcCenter();
}

bool CLine::CanResize(float Factor,Output *pOut)
{
	if (Factor==0.25 || Factor==0.5)
		return true;
	Point p1= point1;
	Point p2= point2;
	CalcCenter();
	p1.x = (p1.x>Center.x) ? (int)(Center.x+Factor*(p1.x-Center.x)) : (int)(Center.x-Factor*(Center.x-p1.x));
	p1.y = (p1.y>Center.y) ? (int)(Center.y+Factor*(p1.y-Center.y)) : (int)(Center.y-Factor*(Center.y-p1.y));
	p2.x = (p2.x>Center.x) ? (int)(Center.x+Factor*(p2.x-Center.x)) : (int)(Center.x-Factor*(Center.x-p2.x));
	p2.y = (p2.y>Center.y) ? (int)(Center.y+Factor*(p2.y-Center.y)) : (int)(Center.y-Factor*(Center.y-p2.y));

	return (pOut->Check_Point(p1) &&pOut->Check_Point(p2));
}

void CLine::Resize(float Factor)
{
	CalcCenter();
	point1.x = (point1.x>Center.x) ? (int)(Center.x+Factor*(point1.x-Center.x)) : (int)(Center.x-Factor*(Center.x-point1.x));
	point1.y = (point1.y>Center.y) ? (int)(Center.y+Factor*(point1.y-Center.y)) : (int)(Center.y-Factor*(Center.y-point1.y));
	point2.x = (point2.x>Center.x) ? (int)(Center.x+Factor*(point2.x-Center.x)) : (int)(Center.x-Factor*(Center.x-point2.x));
	point2.y = (point2.y>Center.y) ? (int)(Center.y+Factor*(point2.y-Center.y)) : (int)(Center.y-Factor*(Center.y-point2.y));
	CalcArea();
}

bool CLine::CheckPointFound(Point P) const{ 

	double a = sqrt((point1.x - P.x)*(point1.x - P.x) +
		(point1.y - P.y)*(point1.y - P.y)) + sqrt((point2.x - P.x)*(point2.x - P.x) + (point2.y - P.y)*(point2.y - P.y));

	double b = sqrt((point1.x - point2.x)*(point1.x - point2.x) + (point1.y - point2.y)*(point1.y - point2.y));
	
	//round
	return floor(a + 0.5) == floor(b + 0.5); 
}

CFigure* CLine::Copy() const{ 
	CFigure* pCopy = new CLine(point1,point2,FigGfxInfo);
	return pCopy;
}
///////////////////////////////////////////////////////////////////////////////////////////
CFigure* CLine::Cut() const{ // cut figures will have the same ID

	CFigure* pCut = Copy();
	pCut->setID(ID);
	return pCut;
}

/////////////////////////////////////////////////////////////////////////////////////////////
bool CLine::CanRotate(int RotationalAngle, Output *pOut) const{

	Point Newcenter;

	Point P1 = point1;
	Point P2 = point2;
	//approximation:
	if((P1.x + P2.x) % 2 != 0) P1.x += 1;
	if((P1.y + P2.y)% 2 != 0) P1.y += 1;

	Newcenter.x =(P1.x + P2.x)/ 2; //as center changed due to approximation
	Newcenter.y = (P1.y + P2.y)/2;

	//Axis Translation to the Center of the line
	P1.x -= Newcenter.x;

	P1.y -= Newcenter.y; 

	P2.x -= Newcenter.x;

	P2.y -= Newcenter.y;

	//Axis Rotation around center of the line
	switch(RotationalAngle){

		//(X,Y)------>(-Y,X) //(Y,-X)
	case 90:
		swap(P1.x,P1.y);
		swap(P2.x,P2.y);
		P1.y *= -1;
		P2.y *= -1;
		break;

		//(X,Y)------>(-X,-Y)
	case 180:
		P1.x *= -1;
		P1.y *= -1;
		P2.x *= -1;
		P2.y *= -1;
		break;

		//(X,Y)------>(Y,-X) //(-Y,X)
	case 270:
		swap(P1.x,P1.y);
		swap(P2.x,P2.y);
		P1.x *= -1;
		P2.x *= -1;
		break;
	}

	//Axis Translation to the original axis
	P1.x += Newcenter.x;  

	P1.y += Newcenter.y;

	P2.x += Newcenter.x;

	P2.y += Newcenter.y;

	return (pOut->Check_Point(P1)&&pOut->Check_Point(P2));
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void CLine::Rotate(int RotationalAngle){

	//approximation:
	if((point1.x + point2.x) % 2 != 0) point1.x += 1;
	if((point1.y + point2.y)% 2 != 0) point1.y += 1;

	CalcCenter(); //as the center changed for approximation

	//Axis Translation to the Center of the line
	point1.x -= Center.x;

	point1.y -= Center.y; 

	point2.x -= Center.x;

	point2.y -= Center.y;
	
	//Axis Rotation around center of the line
	switch(RotationalAngle){

		//(X,Y)------>(-Y,X) //(Y,-X)
	case 90:
		swap(point1.x,point1.y);
		swap(point2.x,point2.y);
		point1.y *= -1;
		point2.y *= -1;
		break;

		//(X,Y)------>(-X,-Y)
	case 180:
		point1.x *= -1;
		point1.y *= -1;
		point2.x *= -1;
		point2.y *= -1;
		break;

		//(X,Y)------>(Y,-X) //(-Y,X)
	case 270:
		swap(point1.x,point1.y);
		swap(point2.x,point2.y);
		point1.x *= -1;
		point2.x *= -1;
		break;
	}

	//Axis Translation to the original axis
	point1.x += Center.x;

	point1.y += Center.y;

	point2.x += Center.x;

	point2.y += Center.y;

	CalcCenter(); //as the center changed due to rotation
}

