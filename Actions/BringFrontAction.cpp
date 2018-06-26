#include "BringFrontAction.h"
#include"../ApplicationManager.h"

BringFrontAction::BringFrontAction(ApplicationManager*pApp):Action(pApp)
{
	saved = false;
}

bool BringFrontAction::ReadActionParameters(){

	return true;
}

bool BringFrontAction::Execute(){

	Output *pOut = pManager->GetOutput();

	//check if there is selected figures
	if(pManager->getSelectedCount() == 0){
		pOut->PrintMessage("There isn't any Selected Figure ,Please choose Select Action First");
		return false;
	}
	//check if we are in the zoom mode
	if(pOut->get_zoom_factor() != 1)
		return false;

	pManager->BringFront();
	pOut->PrintMessage("Bring selected figures front");
	return true;


}

BringFrontAction::~BringFrontAction(void)
{
}
