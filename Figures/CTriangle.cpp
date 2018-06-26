#include "CTriangle.h"
#include "TriangleArea.h"


CTriangle::CTriangle()
{
	Corner1.x=100;
	Corner1.y=100;
	Corner1.x=150;
	Corner1.y=150;
	Corner1.x=200;
	Corner1.y=200;
	///any values
	CalcCenter();
	CalcArea();
}

CTriangle::CTriangle(Point P1 , Point P2,Point P3, GfxInfo FigureGfxInfo ):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;
	CalcCenter();
	CalcArea();
}

void CTriangle:: CalcCenter()
{
	Center.x = (Corner1.x + Corner2.x + Corner3.x)/3;
	Center.y = (Corner1.y + Corner2.y + Corner3.y)/3;	
}

void CTriangle::CalcArea()
{
	Area =abs((Corner1.x*(Corner2.y-Corner3.y) + Corner2.x*(Corner3.y-Corner1.y)+ Corner3.x*(Corner1.y-Corner2.y))/2.0f);
}
void CTriangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	float f=pOut->get_zoom_factor();
	Point C = pOut->get_zoom_center();
	Point P1,P2 ,P3;
	P1.x=(int)(f*(Corner1.x -C.x)+C.x) ; P1.y=(int)(f*(Corner1.y -C.y)+C.y);
	P2.x=(int)(f*(Corner2.x -C.x)+C.x) ; P2.y=(int)(f*(Corner2.y -C.y)+C.y);
	P3.x=(int)(f*(Corner3.x -C.x)+C.x) ; P3.y=(int)(f*(Corner3.y -C.y)+C.y);
	pOut->DrawTria(P1, P2,P3, FigGfxInfo, Selected);
	//PrintInfo(pOut);
}
void CTriangle:: PrintInfo(Output* pOut) const
{
	string str="Triangle: ID = "+to_string(ID);
	str+=" corner1("+to_string( Corner1.y)+","+to_string(Corner1.y)+") , corner2("+to_string(Corner2.x)+","+to_string(Corner2.y)+") ,corner3("+to_string(Corner3.x)+","+to_string(Corner3.y)+")";
	str+="color = red:"+to_string(FigGfxInfo.DrawClr.ucRed)+" green:"+to_string(FigGfxInfo.DrawClr.ucGreen)+" blue:"+to_string(FigGfxInfo.DrawClr.ucBlue);
	if (CFigure::FigGfxInfo.isFilled)
		str+=" fill= red:"+to_string(FigGfxInfo.FillClr.ucRed)+" green:"+to_string(FigGfxInfo.FillClr.ucGreen)+" blue:"+to_string(FigGfxInfo.FillClr.ucBlue);
	else
		str+=" not filled .";
	
	float cmArea = (float)(Area/37.79);
	str+=" Area = "+to_string(cmArea);

	pOut->PrintMessage(str);
}

void CTriangle::Save(ofstream &OutFile) const
{
	/// the triangle type is 2 
	OutFile<<2<<"  "<<ID<<"  "<<Corner1.x<<"  "<<Corner1.y<<"  "<<Corner2.x<<"  "<<Corner2.y<<"  "<<Corner3.x<<"  "<<Corner3.y<<"  "<<FigGfxInfo.BorderWdth<<" ";

	string drwclr=to_string(FigGfxInfo.DrawClr.ucRed)+"  "+to_string(FigGfxInfo.DrawClr.ucGreen)+"  "+to_string(FigGfxInfo.DrawClr.ucBlue)+"  ";
	OutFile<<drwclr;

	string flclr;
	if(FigGfxInfo.isFilled)
		flclr+=to_string(FigGfxInfo.FillClr.ucRed)+"  "+to_string(FigGfxInfo.FillClr.ucGreen)+"  "+to_string(FigGfxInfo.FillClr.ucBlue)+"  ";
	else
		flclr+="NO_FILL";
	OutFile<<flclr<<endl;
}

void CTriangle::Load(ifstream &Infile)
{
	Infile>>ID>>Corner1.x>>Corner1.y>>Corner2.x>>Corner2.y>>Corner3.x>>Corner3.y>>FigGfxInfo.BorderWdth;
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

Point CTriangle:: TopLeft() const //lsa 
{
	if (Corner1.y<Corner2.y && Corner1.y<Corner3.y)
		return Corner1;
	else if (Corner1.y==Corner2.y && Corner1.y<Corner3.y )
	{
		if (Corner1.x<=Corner2.x )
			return Corner1;
		else 
			return Corner2;
	}
	else if (Corner1.y==Corner3.y && Corner1.y<Corner2.y )
	{
		if (Corner1.x<=Corner3.x)
			return Corner1;
		else 
			return Corner3;
	}
	///////////////////
	else if (Corner2.y<Corner1.y && Corner2.y<Corner3.y)
		return Corner2;
	else if (Corner2.y==Corner1.y && Corner2.y<Corner3.y )
	{
		if (Corner2.x<=Corner1.x )
			return Corner2;
		else 
			return Corner1;
	}
	else if (Corner2.y==Corner3.y && Corner2.y<Corner1.y )
	{
		if (Corner2.x<=Corner3.x)
			return Corner2;
		else 
			return Corner3;
	}
	/////////////////////
	else if (Corner3.y<Corner2.y && Corner3.y<Corner1.y)
		return Corner3;
	else if (Corner3.y==Corner2.y && Corner3.y<Corner1.y)
	{
		if (Corner3.x<=Corner2.x )
			return Corner3;
		else 
			return Corner2;
	}
	else /*if (Corner3.y==Corner1.y && Corner3.y<Corner2.y )*/
	{
		if (Corner3.x<=Corner1.x)
			return Corner3;
		else 
			return Corner1;
	}
}

Point CTriangle::MostLeft() const{

	Point min = Corner1;

	if(Corner2.x < min.x) min = Corner2;
	if(Corner3.x < min.x) min = Corner3;

	return min;
}

bool CTriangle::CanMove (Point added , bool up , bool left,Output *pOut) const
{
	Point P1=Corner1;
	Point P2=Corner2;
	Point P3=Corner3;
	if (up)
	{
		P1.y-=added.y;
		P2.y-=added.y;
		P3.y-=added.y;
	}
	else
	{
		P1.y+=added.y;
		P2.y+=added.y;
		P3.y+=added.y;
	}
	if (left)
	{
		P1.x-=added.x;
		P2.x-=added.x;
		P3.x-=added.x;
	}
	else
	{
		P1.x+=added.x;
		P2.x+=added.x;
		P3.x+=added.x;
	}
	return (pOut->Check_Point(P1)&&pOut->Check_Point(P2)&&pOut->Check_Point(P3));
}

void CTriangle::Move(Point added , bool up , bool left)
{
	if (up)
	{
		Corner1.y-=added.y;
		Corner2.y-=added.y;
		Corner3.y-=added.y;
	}
	else
	{
		Corner1.y+=added.y;
		Corner2.y+=added.y;
		Corner3.y+=added.y;
	}
	if (left)
	{
		Corner1.x-=added.x;
		Corner2.x-=added.x;
		Corner3.x-=added.x;
	}
	else
	{
		Corner1.x+=added.x;
		Corner2.x+=added.x;
		Corner3.x+=added.x;
	}
	CalcCenter();
}

bool CTriangle::CanResize(float Factor,Output *pOut)
{
	if (Factor==0.25 || Factor==0.5)
		return true;
	Point p1= Corner1;
	Point p2= Corner2;
	Point p3 =Corner3;
	CalcCenter();
	p1.x = (p1.x>Center.x) ? (int)(Center.x+Factor*(p1.x-Center.x)) : (int)(Center.x-Factor*(Center.x-p1.x));
	p1.y = (p1.y>Center.y) ? (int)(Center.y+Factor*(p1.y-Center.y)) : (int)(Center.y-Factor*(Center.y-p1.y));
	p2.x = (p2.x>Center.x) ? (int)(Center.x+Factor*(p2.x-Center.x)) : (int)(Center.x-Factor*(Center.x-p2.x));
	p2.y = (p2.y>Center.y) ? (int)(Center.y+Factor*(p2.y-Center.y)) : (int)(Center.y-Factor*(Center.y-p2.y));
	p3.x = (p3.x>Center.x) ? (int)(Center.x+Factor*(p3.x-Center.x)) : (int)(Center.x-Factor*(Center.x-p3.x));
	p3.y = (p3.y>Center.y) ? (int)(Center.y+Factor*(p3.y-Center.y)) : (int)(Center.y-Factor*(Center.y-p3.y));

	return (pOut->Check_Point(p1) &&pOut->Check_Point(p2)&& pOut->Check_Point(p3));

}

void CTriangle::Resize(float Factor)
{
	CalcCenter();
	Corner1.x = (Corner1.x>Center.x) ? (int)(Center.x+Factor*(Corner1.x-Center.x)) : (int)(Center.x-Factor*(Center.x-Corner1.x));
	Corner1.y = (Corner1.y>Center.y) ? (int)(Center.y+Factor*(Corner1.y-Center.y)) : (int)(Center.y-Factor*(Center.y-Corner1.y));
	Corner2.x = (Corner2.x>Center.x) ? (int)(Center.x+Factor*(Corner2.x-Center.x)) : (int)(Center.x-Factor*(Center.x-Corner2.x));
	Corner2.y = (Corner2.y>Center.y) ? (int)(Center.y+Factor*(Corner2.y-Center.y)) : (int)(Center.y-Factor*(Center.y-Corner2.y));
	Corner3.x = (Corner3.x>Center.x) ? (int)(Center.x+Factor*(Corner3.x-Center.x)) : (int)(Center.x-Factor*(Center.x-Corner3.x));
	Corner3.y = (Corner3.y>Center.y) ? (int)(Center.y+Factor*(Corner3.y-Center.y)) : (int)(Center.y-Factor*(Center.y-Corner3.y));
	CalcArea();
}

bool CTriangle::CheckPointFound(Point P) const{
	/* A function to check whether point P(x, y) lies inside the triangle formed 
	by A(x1, y1), B(x2, y2) and C(x3, y3) */

	/* Calculate area of triangle ABC */
	float A = area (Corner1.x,Corner1.y, Corner2.x, Corner2.y, Corner3.x, Corner3.y);

	/* Calculate area of triangle PBC */  
	float A1 = area (P.x, P.y, Corner2.x, Corner2.y, Corner3.x, Corner3.y);

	/* Calculate area of triangle PAC */  
	float A2 = area (Corner1.x,Corner1.y, P.x, P.y, Corner3.x, Corner3.y);

	/* Calculate area of triangle PAB */   
	float A3 = area (Corner1.x,Corner1.y, Corner2.x, Corner2.y, P.x, P.y);

	/* Check if sum of A1, A2 and A3 is same as A */
	return (A == A1 + A2 + A3);

}

CFigure* CTriangle::Copy() const{ 

	CFigure* pCopy = new CTriangle(Corner1,Corner2,Corner3,FigGfxInfo);
	return pCopy;
}


CFigure* CTriangle::Cut() const{ // cut figures will have the same ID

	CFigure* pCut = Copy();
	pCut->setID(ID);
	return pCut;
}

bool CTriangle::CanRotate(int RotationalAngle, Output* pOut) const{

	Point Newcenter;

	Point P1=Corner1;
	Point P2=Corner2;
	Point P3=Corner3;

	//Approximation
	if((Corner1.x + Corner2.x + P3.x)%3 != 0) {
		if ((P1.x + P2.x + P3.x + 1) %3 == 0) P1.x += 1;
		else P1.x -= 1;
	}
	if((P1.y + P2.y + P3.y) %3 != 0){
		if((P1.y + P2.y + P3.y+1)%3 == 0) P1.y += 1;
		else P1.y -= 1;
	}


	////Center of Tringle
	Newcenter.x = (P1.x + P2.x + P3.x)/3; // center will chage due to approximation
	Newcenter.y = (P1.y + P2.y + P3.y)/3;

	//Axis Translation to the Center of the Triangle
	P1.x -= Newcenter.x;

	P1.y -= Newcenter.y;

	P2.x -= Newcenter.x;

	P2.y -= Newcenter.y;

	P3.x -= Newcenter.x;

	P3.y -= Newcenter.y;

	//Axis Rotation around center of Triangle
	switch(RotationalAngle){
		//(X,Y)------>(Y,-X)
	case 90:
		swap(P1.x,P1.y);
		swap(P2.x,P2.y);
		swap(P3.x,P3.y);
		P1.y *= -1;
		P2.y *= -1;
		P3.y *= -1;
		break;

		//(X,Y)------>(-X,-Y)
	case 180:
		P1.x *= -1;
		P1.y *= -1;
		P2.x *= -1;
		P2.y *= -1;
		P3.x *= -1;
		P3.y *= -1;
		break;

		//(X,Y)------>(Y,-X) //(-Y,X)
	case 270:
		swap(P1.x,P1.y);
		swap(P2.x,P2.y);
		swap(P3.x,P3.y);
		P1.x *= -1;
		P2.x *= -1;
		P3.x *= -1;
		break;
	}

	//Axis Translation to the original axis
	P1.x +=  Newcenter.x;

	P1.y += Newcenter.y;

	P2.x += Newcenter.x;

	P2.y += Newcenter.y;

	P3.x += Newcenter.x;

	P3.y += Newcenter.y;

	return (pOut->Check_Point(P1)&&pOut->Check_Point(P2)&&pOut->Check_Point(P3));
}

void CTriangle::Rotate(int RotationalAngle){

	/*Point Center;*/

	//Approximation
	if((Corner1.x + Corner2.x + Corner3.x)%3 != 0) {
		if ((Corner1.x + Corner2.x + Corner3.x + 1) %3 == 0) Corner1.x += 1;
		else Corner1.x -= 1;
	}
	if((Corner1.y + Corner2.y + Corner3.y) %3 != 0){
		if((Corner1.y + Corner2.y + Corner3.y+1)%3 == 0) Corner1.y += 1;
		else Corner1.y -= 1;
	}


	CalcCenter(); // as center wil change due to approximation

	//Axis Translation to the Center of the Triangle
	Corner1.x -= Center.x;

	Corner1.y -= Center.y;

	Corner2.x -= Center.x;

	Corner2.y -= Center.y;

	Corner3.x -= Center.x;

	Corner3.y -= Center.y;

	//Axis Rotation around center of Triangle
	switch(RotationalAngle){
		//(X,Y)------>(-Y,X) //(Y,-X)
	case 90:
		swap(Corner1.x,Corner1.y);
		swap(Corner2.x,Corner2.y);
		swap(Corner3.x,Corner3.y);
		Corner1.y *= -1;
		Corner2.y *= -1;
		Corner3.y *= -1;
		break;

		//(X,Y)------>(-X,-Y)
	case 180:
		Corner1.x *= -1;
		Corner1.y *= -1;
		Corner2.x *= -1;
		Corner2.y *= -1;
		Corner3.x *= -1;
		Corner3.y *= -1;
		break;

		//(X,Y)------>(Y,-X) //(-Y,X)
	case 270:
		swap(Corner1.x,Corner1.y);
		swap(Corner2.x,Corner2.y);
		swap(Corner3.x,Corner3.y);
		Corner1.x *= -1;
		Corner2.x *= -1;
		Corner3.x *= -1;
		break;
	}

	//Axis Translation to the original axis
	Corner1.x +=  Center.x; 

	Corner1.y += Center.y;

	Corner2.x += Center.x;

	Corner2.y += Center.y;

	Corner3.x += Center.x;

	Corner3.y += Center.y;

	CalcCenter(); //as center will cahnge due to rotation
}
