#include "ChangeFillClrAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ChangeFillClrAction::ChangeFillClrAction(ApplicationManager * pApp):Action(pApp)
{
	saved = false;
}

bool ChangeFillClrAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	
	pOut->CreateColorSubMenu();
	pOut->PrintMessage("Choose The Filling Color");
	 FillColor = pIn->GetUserColor();
	 if(FillColor.ucBlue == pOut->getHighlightedColor())
		return false;
	pOut->ClearStatusBar();
	return true;
				
}
bool ChangeFillClrAction::Execute()
{
	Output *pOut=pManager->GetOutput();
	if (!ReadActionParameters())
	{
		pOut->PrintMessage("ERROR! You pressed an invalid point");
		return false;
	}
	bool change=pManager->ChangeFillClr(FillColor);
	if (change == false)
		pOut->setCrntFillColor(FillColor);
	pOut->ClearDrawArea();

	return true;
}

ChangeFillClrAction::~ChangeFillClrAction(void)
{
}

