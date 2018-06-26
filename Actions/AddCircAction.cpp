#include "AddCircAction.h"
#include "..\Figures\CCircle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddCircAction::AddCircAction(ApplicationManager * pApp):Action(pApp)
{
	saved = false;
}

int AddCircAction::CalculateRadius()const
{
	return int(sqrt(pow(P1.x-P2.x,2)+pow(P1.y-P2.y,2)));
} 

bool AddCircAction::Check_Radius() const
{
	Point P3=P1,P4=P1;
	P3.x+=Radius; P3.y+=Radius;
	P4.x-=Radius; P4.y-=Radius;
	Output *pOut=pManager->GetOutput();
	return (pOut->Check_Point(P3) && pOut->Check_Point(P4));
}

bool AddCircAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Circle: Click at the Center");
	
	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
	if(!pOut->Check_Point(P1))
		return false;
	pOut->PrintMessage("New Circle: Click at an end point");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	Radius=CalculateRadius();

	if(!Check_Radius())
		return false;
	CircGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	CircGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircGfxInfo.FillClr = pOut->getCrntFillColor();
	CircGfxInfo.BorderWdth = pOut->getCrntPenWidth();

	pOut->ClearStatusBar();
	return true;
}

//Execute the action
bool AddCircAction::Execute() 
{
	
	//This action needs to read some parameters first
	Output *pOut=pManager->GetOutput();

	//check if the graph is in the zoom mode or not
	if(pOut->get_zoom_factor() != 1)
		return false;

	if (!ReadActionParameters())
	{
		pOut->PrintMessage("ERROR! You pressed an invalid point");
		return false;
	}
	
	
	//Create a circle with the parameters read from the user
	CCircle *C=new CCircle(P1, Radius, CircGfxInfo);

	//Add the circle to the list of figures
	pManager->AddFigure(C);

	return true;
}
