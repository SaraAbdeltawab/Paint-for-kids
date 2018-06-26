#include "ChangeBorderAction.h"
#include"../ApplicationManager.h"


ChangeBorderAction::ChangeBorderAction(ApplicationManager* pApp):Action(pApp)
{
	saved = false;
}
bool ChangeBorderAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	BorderWidthAction ActBorder;

	pOut->CreateBorderWidthSubMenu();

	pOut->PrintMessage("Choose The BorderWidth");

	//get the user required border width

	do{

		ActBorder = pIn->GetUserBorderWidth(); 

		switch(ActBorder){

		case TWO:
			BorderWidth = 2;
			break;

		case THREE:
			BorderWidth = 3;
			break;

		case FOUR:
			BorderWidth = 4;
			break;

		case FIVE:
			BorderWidth = 5;
			break;

		case SIX:
			BorderWidth = 6;
			break;

		case CLOSE_BORDERWIDTH:
			return false;
			break;
		}

	}while(ActBorder == EMPTY_BORDERWIDTH);

	pOut->ClearStatusBar();

	return true;
}

bool ChangeBorderAction:: Execute()
{	
	Output *pOut=pManager->GetOutput();

	//check if the graoh in zoom mode
	if(pOut->get_zoom_factor() != 1)
		return false;

	if(ReadActionParameters())
	{
		pOut->ClearDrawArea();

		bool change = pManager->ChangeBorderWidth(BorderWidth);
		if (change == false)
			pOut->setCrntPenWidth(BorderWidth); 
		pOut->PrintMessage("Change Border Width");
		return true;
	}

	return false;
}


ChangeBorderAction::~ChangeBorderAction()
{
}
