#include "ZoomOutAction.h"
#include "../ApplicationManager.h"
#include "ChangeBorderAction.h"
#include "../GUI\input.h"
#include "../GUI\Output.h"

ZoomOutAction::ZoomOutAction(ApplicationManager * pApp):Action(pApp)
{
	Output* pOut = pManager->GetOutput();
	pOut->setZoomMode(true);
}

bool ZoomOutAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Click to the Zoom Center Point");
	
	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P.x, P.y);
	if(!pOut->Check_Point(P))
		return false;
	pOut->ClearStatusBar();
	return true;
}
bool ZoomOutAction::Execute()
{
	Output *pOut=pManager->GetOutput();
	if (!ReadActionParameters())
	{
		pOut->PrintMessage("ERROR! You pressed an invalid point");
		return false;
	}
	
	pOut->set_zoom_center(P);
	pOut->set_zoom_factor(0.5);
	pManager->Zooming(0.5);
	return true;
}
ZoomOutAction::~ZoomOutAction(void)
{
}
