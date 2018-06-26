#include "CCircle.h"


CCircle::CCircle()
{
	Center.x=150;
	Center.y=150;
	Radius=30;
	CalcArea();
	////ay values
}
CCircle::CCircle(Point P1, int R, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Center = P1;
	Radius = R;
	CalcArea();
}
	
void CCircle :: CalcArea()
{
	Area= (float)(3.14*pow(Radius,2));
}

void CCircle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen
	float f=pOut->get_zoom_factor();
	Point C = pOut->get_zoom_center();
	Point center ;
	center.x=(int)(f*(Center.x -C.x)+C.x) ; center.y = (int)(f*(Center.y -C.y)+C.y);

	pOut->DrawCirc(center, (int)(f*Radius), FigGfxInfo, Selected);
	//PrintInfo(pOut);
}

void CCircle:: PrintInfo(Output* pOut) const
{
	string str="Circle: ID = "+to_string(ID);
	str+=" center ("+to_string( Center.x)+","+to_string(Center.y)+") , Radius="+to_string(Radius);
	str+=" color = red:"+to_string(FigGfxInfo.DrawClr.ucRed)+" green:"+to_string(FigGfxInfo.DrawClr.ucGreen)+" blue:"+to_string(FigGfxInfo.DrawClr.ucBlue);
	if (CFigure::FigGfxInfo.isFilled)
		str+=" fill= red:"+to_string(FigGfxInfo.FillClr.ucRed)+" green:"+to_string(FigGfxInfo.FillClr.ucGreen)+" blue:"+to_string(FigGfxInfo.FillClr.ucBlue);
	else
		str+=" not filled .";
	float cmArea = (float)(Area/37.79);
	str+=" Area = "+to_string(cmArea);
	pOut->PrintMessage(str);
}

void CCircle::Save(ofstream &OutFile) const
{
	/// The circle is type 3
	OutFile<<3<<"  "<<ID<<"  "<<Center.x<<"  "<<Center.y<<"  "<<Radius<<"  "<<FigGfxInfo.BorderWdth<<" ";
	
	string drwclr=to_string(FigGfxInfo.DrawClr.ucRed)+"  "+to_string(FigGfxInfo.DrawClr.ucGreen)+"  "+to_string(FigGfxInfo.DrawClr.ucBlue)+"  ";
	OutFile<<drwclr;

	string flclr;
	if(FigGfxInfo.isFilled)
		flclr+=to_string(FigGfxInfo.FillClr.ucRed)+"  "+to_string(FigGfxInfo.FillClr.ucGreen)+"  "+to_string(FigGfxInfo.FillClr.ucBlue)+"  ";
	else  
		flclr+="NO_FILL";
	OutFile<<flclr<<endl;
}

void CCircle::Load(ifstream &Infile)
{
	Infile>>ID>>Center.x>>Center.y>>Radius>>FigGfxInfo.BorderWdth;
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
	CalcArea();
}

Point CCircle:: TopLeft() const
{
	Point P=Center;
	P.y=Center.y-Radius;
	return P;
}
Point CCircle::MostLeft() const
{
	Point P = Center;
	P.x = Center.x - Radius;
	return P;
}
bool CCircle::CanMove (Point added , bool up , bool left,Output *pOut) const
{
	Point P1; P1.x=Center.x+Radius; P1.y=Center.y+Radius;
	Point P2; P2.x=Center.x-Radius; P2.y=Center.y-Radius;
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

void CCircle::Move(Point added , bool up , bool left)
{
	Center.y= up ? Center.y-added.y : Center.y+added.y;
	Center.x= left ? Center.x-added.x : Center.x+added.x;
}

bool CCircle::CanResize(float Factor,Output *pOut) 
{
	if (Factor==0.25 || Factor==0.5)
		return true;
	int r;
	if (Factor==2)
		r=Radius*2;
	else
		r=Radius*4;
	Point P1; P1.x=Center.x+r; P1.y=Center.y+r;
	Point P2; P2.x=Center.x-r; P2.y=Center.y-r;
	return (pOut->Check_Point(P1)&&pOut->Check_Point(P2));
}

void CCircle::Resize(float Factor)
{
	float size=Radius*Factor;
	Radius =(int)size;
	CalcArea();
}


bool CCircle::CheckPointFound(Point P) const{
	return (P.x - Center.x)*(P.x - Center.x) + (P.y - Center.y)* (P.y - Center.y) <= Radius*Radius;
}

CFigure* CCircle::Copy() const{

	CFigure* pCopy = new CCircle(Center,Radius,FigGfxInfo);
	return pCopy;
}

CFigure* CCircle::Cut() const{ // cut figures will have the same ID

	CFigure* pCut = Copy();
	pCut->setID(ID);
	return pCut;
}



bool CCircle::CanRotate(int RotationalAngle, Output* pOut) const{ return true;}
////////////////////////////////////////////////////////////
void CCircle::Rotate(int RotationalAngle){}

///////////////////////////////////////////////////////////



