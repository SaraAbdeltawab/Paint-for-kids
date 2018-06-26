#include "ZoomInAction.h"
#include "../ApplicationManager.h"
#include "ChangeBorderAction.h"
#include "../GUI\input.h"
#include "../GUI\Output.h"

ZoomInAction::ZoomInAction(ApplicationManager * pApp):Action(pApp)
{
	Output* pOut = pManager->GetOutput();
	pOut->setZoomMode(true);
}

bool ZoomInAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Click to the Zoom Center Point");
	
	
	pIn->GetPointClicked(P.x, P.y);
	if(!pOut->Check_Point(P))
		return false;
	pOut->ClearStatusBar();
	return true;
}
bool ZoomInAction::Execute() 
{

	//This action needs to read some parameters first
	Output *pOut=pManager->GetOutput();
	if (!ReadActionParameters())
	{
		pOut->PrintMessage("ERROR! You pressed an invalid point");
		return false;
	}
	
	pOut->set_zoom_center(P);
	pOut->set_zoom_factor(2);
	pManager->Zooming(2);
	
	return true;
}
ZoomInAction::~ZoomInAction(void)
{
}
