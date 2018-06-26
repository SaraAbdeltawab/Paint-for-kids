#include "ChangeBKAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ChangeBKAction::ChangeBKAction(ApplicationManager * pApp):Action(pApp)
{
	saved = false;
}

bool ChangeBKAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	
	pOut->CreateColorSubMenu();
	pOut->PrintMessage("Choose The Background Color");

	UserColor = pIn->GetUserColor();

	if(UserColor.ucBlue == pOut->getHighlightedColor())
		return false;

	pOut->ClearStatusBar();
	return true;
}

bool ChangeBKAction::Execute()
{
	Output *pOut=pManager->GetOutput();

	//check if the graph in the zoom mode
	if(pOut->get_zoom_factor() != 1)
		return false;

	if (!ReadActionParameters())
	{
		pOut->PrintMessage("ERROR! You pressed an invalid point");
		return false;
	}
	
	pOut->setCrntBKGrndColor(UserColor);
	pOut->ClearDrawArea();
	pOut->PrintMessage("Change Background Color");
	return true;
}
ChangeBKAction::~ChangeBKAction(void)
{
}
