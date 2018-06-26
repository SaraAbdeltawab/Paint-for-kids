#include "AddTriaAction.h"

#include "..\Figures\CTriangle.h"

#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddTriaAction::AddTriaAction(ApplicationManager * pApp):Action(pApp)
{
	saved = false;
}


bool AddTriaAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Triangle: Click at first corner");
	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
	if (!pOut->Check_Point(P1))
		return false;

	pOut->PrintMessage("New Triangle: Click at second corner");
	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	if(!pOut->Check_Point(P2))
		return false;


	pOut->PrintMessage("New Triangle: Click at third corner");
	//Read 3rd corner and store in point P3
	pIn->GetPointClicked(P3.x, P3.y);
	if (!pOut->Check_Point(P3))
		return false;

	TriaGfxInfo.isFilled = false;//default is not filled
	//get drawing, filling colors and pen width from the interface
	TriaGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TriaGfxInfo.FillClr = pOut->getCrntFillColor();
	TriaGfxInfo.BorderWdth = pOut->getCrntPenWidth();

	pOut->ClearStatusBar();
	return true;
}


bool AddTriaAction::Execute() 
{
	//This action needs to read some parameters first
	Output *pOut=pManager->GetOutput();
	if(pOut->get_zoom_factor() != 1)
		return false;
	if (!ReadActionParameters())
	{
		pOut->PrintMessage("ERROR! You pressed an invalid point");
		return false;
	}
	

	//Create a triangle with the parameters read from the user
	CTriangle *T=new CTriangle(P1, P2, P3, TriaGfxInfo);

	//Add the triangle to the list of figures
	pManager->AddFigure(T);
	return true;
}

 AddTriaAction::~AddTriaAction()
 {}