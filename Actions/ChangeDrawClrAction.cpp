#include "ChangeDrawClrAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"

ChangeDrawClrAction::ChangeDrawClrAction(ApplicationManager * pApp):Action(pApp)
{
	saved = false;
}

bool ChangeDrawClrAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->CreateColorSubMenu();
	pOut->PrintMessage("Choose The Drawing Color");

	DrawColor = pIn->GetUserColor();
	if(DrawColor.ucBlue == pOut->getHighlightedColor())		
		return false;

	pOut->ClearStatusBar();
	return true;
}

bool ChangeDrawClrAction::Execute()
{
	Output *pOut=pManager->GetOutput();

	if (!ReadActionParameters())
	{
		pOut->PrintMessage("ERROR! You pressed an invalid point");
		return false;
	}

	//check if the user want to change the selected figres or the UI draw color
	bool change = pManager->ChangeDrawClr(DrawColor);
	if (change == false)
		pOut->setCrntDrawColor(DrawColor);

	pOut->ClearDrawArea();

	return true;
}

ChangeDrawClrAction::~ChangeDrawClrAction(void)
{
}
