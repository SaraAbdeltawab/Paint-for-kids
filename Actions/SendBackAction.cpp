#include "SendBackAction.h"
#include"../ApplicationManager.h"

SendBackAction::SendBackAction(ApplicationManager* pApp):Action(pApp)
{
	saved = false;
}

bool SendBackAction::ReadActionParameters(){return true;}//in order not to be pure virtual

bool SendBackAction::Execute(){

	Output * pOut = pManager->GetOutput();

	if(pManager->getSelectedCount() == 0){
		pOut->PrintMessage("There isn't any Selected Figure ,Please choose Select Action First");
		return false;
	}
	pManager->SendBack();
	pOut->PrintMessage("Send selected figures back");
	return true;
}

SendBackAction::~SendBackAction(void)
{
}
