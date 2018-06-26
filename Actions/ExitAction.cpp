#include "ExitAction.h"
#include "..\ApplicationManager.h"

ExitAction::ExitAction(ApplicationManager* pApp): Action(pApp)
{
}

bool  ExitAction::ReadActionParameters(){

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Do You really want to exit? y :( / n :D ");
	string exit = pIn->GetSrting(pOut);
	string save;

	if(exit != "y"){
		pOut->ClearStatusBar();
		return false;
	}

	if(!saved) {

		pOut->PrintMessage("Do You want to save changes ? y / n");
		save = pIn->GetSrting(pOut);

		if(save == "y") pManager->ExecuteAction(SAVE);

	}
	pOut->PrintMessage("GoodBye");
	return true;
}

bool ExitAction::Execute(){ //clean up//????????????

	return ReadActionParameters();

}

ExitAction::~ExitAction()
{}
