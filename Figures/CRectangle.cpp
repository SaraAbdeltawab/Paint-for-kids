#include "CRectangle.h"


CRectangle::CRectangle()
{
	Corner1.x=100;
	Corner1.y=100;
	Corner2.x=150;
	Corner2.y=150;
	CalcCenter();
	CalcArea();
}

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	CalcCenter();
	CalcArea();
}

void CRectangle:: CalcCenter()
{
	Center.x = (Corner1.x + Corner2.x)/ 2;
	Center.y = (Corner1.y + Corner2.y)/2;
}

void CRectangle::CalcArea()
{
	Area = (float)(abs(Corner1.x-Corner2.x)*abs(Corner1.y-Corner2.y)) ;
}

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	float f=pOut->get_zoom_factor();
	Point C = pOut->get_zoom_center();
	Point P1,P2 ;
	P1.x=(int)(f*(Corner1.x -C.x)+C.x) ; P1.y=(int)(f*(Corner1.y -C.y)+C.y);
	P2.x=(int)(f*(Corner2.x -C.x)+C.x) ; P2.y=(int)(f*(Corner2.y -C.y)+C.y);
	pOut->DrawRect(P1, P2, FigGfxInfo, Selected);
	//PrintInfo(pOut);
}

void  CRectangle::PrintInfo(Output* pOut) const
{
	string str="Rectangle: ID = "+to_string(ID);
	str+=" corner1("+to_string( Corner1.x)+","+to_string(Corner1.y)+") ,corner2("+to_string(Corner2.x)+","+to_string(Corner2.y)+")";
	str+=" color = red:"+to_string(FigGfxInfo.DrawClr.ucRed)+" green:"+to_string(FigGfxInfo.DrawClr.ucGreen)+" blue:"+to_string(FigGfxInfo.DrawClr.ucBlue);
	if (CFigure::FigGfxInfo.isFilled)
		str+=" fill= red:"+to_string(FigGfxInfo.FillClr.ucRed)+" green:"+to_string(FigGfxInfo.FillClr.ucGreen)+" blue:"+to_string(FigGfxInfo.FillClr.ucBlue);
	else
		str+=" not filled .";
	float cmArea = (float)(Area/37.79);
	str+=" Area = "+to_string(cmArea);
	pOut->PrintMessage(str);
}

void CRectangle::Save(ofstream &OutFile) const
{
	//rectangle is no 1 in the enum
	OutFile<<1<<"  "<<ID<<"  "<<Corner1.x<<"  "<<Corner1.y<<"  "<<Corner2.x<<"  "<<Corner2.y<<"  "<<FigGfxInfo.BorderWdth<<" ";
	string drwclr=to_string(FigGfxInfo.DrawClr.ucRed)+"  "+to_string(FigGfxInfo.DrawClr.ucGreen)+"  "+to_string(FigGfxInfo.DrawClr.ucBlue)+"  ";
	OutFile<<drwclr;

	string flclr;
	if(FigGfxInfo.isFilled)
		flclr+=to_string(FigGfxInfo.FillClr.ucRed)+"  "+to_string(FigGfxInfo.FillClr.ucGreen)+"  "+to_string(FigGfxInfo.FillClr.ucBlue)+"  ";
	else
		flclr+="NO_FILL";
	OutFile<<flclr<<endl;
}

void CRectangle::Load(ifstream &Infile)
{
	Infile>>ID>>Corner1.x>>Corner1.y>>Corner2.x>>Corner2.y>>FigGfxInfo.BorderWdth;
	if (idgenerator<=ID)
		idgenerator=ID+1;
	int r,g,b;
	Infile>>r>>g>>b;
	color drw(r,g,b);
	FigGfxInfo.DrawClr=drw;
	string str;
	getline(Infile,str,'\n');
	if (str.find("NO_FILL") ==-1)
	{
		FigGfxInfo.isFilled=true;

		r=stoi(str);
		del_from_string(str,r);
		g=stoi(str);
		del_from_string(str,g);
		b=stoi(str);
		del_from_string(str,b);
		color fill(r,g,b);
		FigGfxInfo.FillClr=fill;
	}
	else 
		FigGfxInfo.isFilled=false;
	CalcCenter();
	CalcArea();
}

Point CRectangle:: TopLeft() const
{
	Point p;
	p.x=min(Corner1.x,Corner2.x);
	p.y=min(Corner1.y,Corner2.y);
	return p;
}

Point CRectangle::MostLeft() const{
	return TopLeft();
}

bool CRectangle::CanMove (Point added , bool up , bool left,Output *pOut) const
{
	Point P1=Corner1;
	Point P2=Corner2;
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
	return (pOut->Check_Point(P1)&&pOut->Check_Point(P2));
}

void CRectangle::Move(Point added , bool up , bool left)
{
	if (up)
	{
		Corner1.y-=added.y;
		Corner2.y-=added.y;
	}
	else
	{
		Corner1.y+=added.y;
		Corner2.y+=added.y;
	}
	if (left)
	{
		Corner1.x-=added.x;
		Corner2.x-=added.x;
	}
	else
	{
		Corner1.x+=added.x;
		Corner2.x+=added.x;
	}
	CalcCenter();
}


bool CRectangle::CanResize(float Factor,Output *pOut) 
{
	if (Factor==0.25 || Factor==0.5)
		return true;
	Point p1= Corner1;
	Point p2= Corner2;
	CalcCenter();
	p1.x = (p1.x>Center.x) ? (int)(Center.x+Factor*(p1.x-Center.x)) : (int)(Center.x-Factor*(Center.x-p1.x));
	p1.y = (p1.y>Center.y) ? (int)(Center.y+Factor*(p1.y-Center.y)) : (int)(Center.y-Factor*(Center.y-p1.y));
	p2.x = (p2.x>Center.x) ? (int)(Center.x+Factor*(p2.x-Center.x)) : (int)(Center.x-Factor*(Center.x-p2.x));
	p2.y = (p2.y>Center.y) ? (int)(Center.y+Factor*(p2.y-Center.y)) : (int)(Center.y-Factor*(Center.y-p2.y));

	return (pOut->Check_Point(p1) &&pOut->Check_Point(p2));

}

void CRectangle::Resize(float Factor)
{
	CalcCenter();
	Corner1.x = (Corner1.x>Center.x) ? (int)(Center.x+Factor*(Corner1.x-Center.x)) : (int)(Center.x-Factor*(Center.x-Corner1.x));
	Corner1.y = (Corner1.y>Center.y) ? (int)(Center.y+Factor*(Corner1.y-Center.y)) : (int)(Center.y-Factor*(Center.y-Corner1.y));
	Corner2.x = (Corner2.x>Center.x) ? (int)(Center.x+Factor*(Corner2.x-Center.x)) : (int)(Center.x-Factor*(Center.x-Corner2.x));
	Corner2.y = (Corner2.y>Center.y) ? (int)(Center.y+Factor*(Corner2.y-Center.y)) : (int)(Center.y-Factor*(Center.y-Corner2.y));
	CalcArea();
}

bool CRectangle::CheckPointFound(Point P)const{
	return P.x <= max (Corner1.x,Corner2.x) && P.x >= min (Corner1.x,Corner2.x) && P.y <= max (Corner1.y,Corner2.y) && 
		P. y >= min (Corner1.y,Corner2.y);
}

CFigure* CRectangle::Copy() const{ 

	CFigure* pCopy = new CRectangle(Corner1,Corner2,FigGfxInfo);
	return pCopy;
}

CFigure* CRectangle::Cut() const{ // cut figures will have the same ID

	CFigure* pCut = Copy();
	pCut->setID(ID);
	return pCut;
}


bool CRectangle::CanRotate(int RotationalAngle, Output* pOut) const{

	Point Newcenter;

	//Point Center;
	Point P1=Corner1;
	Point P2=Corner2;

	//Approximation
	if((P1.x + P2.x)%2 != 0) P1.x += 1;
	if((P1.y + P2.y) %2 != 0) P1.y += 1;


	////Center of rectangle
	//Center.x =  abs(P1.x - P2.x)/2 + min( P1.x, P2.x);
	//Center.y = abs(P1.y - P2.y)/2 + min(P1.y, P2.y);

	Newcenter.x =(P1.x + P2.x)/ 2; //as center changed due to approximation
	Newcenter.y = (P1.y + P2.y)/2;

	//Axis Translation to the Center of the rectangle
	P1.x -= Newcenter.x;

	P1.y -= Newcenter.y;

	P2.x -= Newcenter.x;

	P2.y -= Newcenter.y;

	//Axis Rotation around center of rectangle
	switch(RotationalAngle){
		//(X,Y)------>(Y,-X)
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

		//(X,Y)------>(-Y,X)
	case 270:
		swap(P1.x,P1.y);
		swap(P2.x,P2.y);
		P1.x *= -1;
		P2.x *= -1;
		break;
	}

	//Axis Translation to the original axis
	P1.x +=  Newcenter.x; 

	P1.y += Newcenter.y;

	P2.x += Newcenter.x;

	P2.y += Newcenter.y;

	return (pOut->Check_Point(P1)&&pOut->Check_Point(P2));

}

void CRectangle::Rotate(int RotationalAngle){

	//Point Center;

	//Approximation
	if((Corner1.x - Corner2.x)%2 != 0) Corner1.x += 1;
	if((Corner1.y - Corner2.y) %2 != 0) Corner1.y += 1;

	CalcCenter(); //as center will change due to approximation

	////Center of rectangle
	//Center.x =  abs(Corner1.x - Corner2.x)/2 + min( Corner1.x, Corner2.x);
	//Center.y = abs(Corner1.y - Corner2.y)/2 + min(Corner1.y, Corner2.y);

	//Axis Translation to the Center of the rectangle
	Corner1.x -= Center.x;

	Corner1.y -= Center.y;

	Corner2.x -= Center.x;

	Corner2.y -= Center.y;


	//Axis Rotation around center of rectangle
	switch(RotationalAngle){
		//(X,Y)------>(Y,-X)
	case 90:
		swap(Corner1.x,Corner1.y);
		swap(Corner2.x,Corner2.y);
		Corner1.y *= -1;
		Corner2.y *= -1;
		break;

		//(X,Y)------>(-X,-Y)
	case 180:
		Corner1.x *= -1;
		Corner1.y *= -1;
		Corner2.x *= -1;
		Corner2.y *= -1;
		break;

		//(X,Y)------>(-Y,X)
	case 270:
		swap(Corner1.x,Corner1.y);
		swap(Corner2.x,Corner2.y);
		Corner1.x *= -1;
		Corner2.x *= -1;
		break;
	}

	//Axis Translation to the original axis
	Corner1.x +=  Center.x; 

	Corner1.y += Center.y;

	Corner2.x += Center.x;

	Corner2.y += Center.y;

	CalcCenter(); //as center will change de to rotation
}