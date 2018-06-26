#include "AddLineAction.h"
#include "..\Figures\CLine.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

AddLineAction::AddLineAction(ApplicationManager * pApp):Action(pApp)
{
	saved = false;
}

bool AddLineAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Line: Click at first point");
	
		//Read 1st point and store in point P1
		pIn->GetPointClicked(P1.x, P1.y);
	if(!pOut->Check_Point(P1))
		return false;

	pOut->PrintMessage("New Line: Click at second point");

		//Read 2nd point and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	if(!pOut->Check_Point(P2))
		return false;

	LineGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	LineGfxInfo.DrawClr = pOut->getCrntDrawColor();
	LineGfxInfo.FillClr = pOut->getCrntFillColor();
	LineGfxInfo.BorderWdth = pOut->getCrntPenWidth();

	pOut->ClearStatusBar();
	return true;
}

//Execute the action
bool AddLineAction::Execute() 
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
	
	//Create a Line with the parameters read from the user
	CLine *L=new CLine(P1, P2, LineGfxInfo);

	//Add the Line to the list of figures
	pManager->AddFigure(L);
	return true;
}
