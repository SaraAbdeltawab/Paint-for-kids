#include "DeleteAction.h"
#include "../ApplicationManager.h"

DeleteAction::DeleteAction(ApplicationManager *pApp):Action(pApp)
{
	saved = false;
}

bool DeleteAction::ReadActionParameters(){

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	int SelectedCount = pManager->getSelectedCount();

	if(SelectedCount == 0){
		pOut->PrintMessage("There isn't any Selected Figure ,Please choose Select Action First");
		return false;
	}

	string msg = "Do you really want to delete " + to_string(SelectedCount) + " figure(s) ? y/n ";
	pOut->PrintMessage(msg);

	string str = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
	if(str == "y") return true;
	else return false;
} 

bool DeleteAction::Execute(){

	if(ReadActionParameters()){
		pManager->Delete();
		return true;
	}

	return false;
}

DeleteAction::~DeleteAction(void)
{}
