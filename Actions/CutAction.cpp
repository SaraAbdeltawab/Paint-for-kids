#include "CutAction.h"
#include "..\ApplicationManager.h"

CutAction::CutAction(ApplicationManager *pApp):Action(pApp)
{
	saved = false;
}

bool CutAction::ReadActionParameters(){

	return true;
} // in order not to be pure virtual 

bool CutAction::Execute(){


	Output* pOut = pManager->GetOutput();

	if(pManager->getSelectedCount() == 0){
		pOut->PrintMessage("There isn't any Selected Figure ,Please choose Select Action First");
		return false;
	}

	if(pOut->get_zoom_factor() != 1)
		return false;

	pOut->PrintMessage("Cut selected figures front");
	pManager->Cut();
	return true;

}

CutAction::~CutAction()
{}
