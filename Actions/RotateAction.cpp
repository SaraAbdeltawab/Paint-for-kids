#include "RotateAction.h"
#include"../ApplicationManager.h"

RotateAction::RotateAction(ApplicationManager*pApp):Action(pApp)
{
	saved = false;
}

bool RotateAction::ReadActionParameters(){

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	if(pManager->getSelectedCount() == 0){
		pOut->PrintMessage("There isn't any Selected Figure ,Please choose Select Action First");
		return false;
	}

	RotationAction ActRotation;

	pOut->CreateRotationAngleSubMenu();

	pOut->PrintMessage("Choose The RotationalAngle");

	do{

		ActRotation = pIn->GetUserRotationAngle(); 

		switch(ActRotation){

		case NINTY:
			RotationalAngle = 90;
			break;

		case ONEEIGHTY:
			RotationalAngle = 180;
			break;

		case TWOSEVENTY:
			RotationalAngle = 270;
			break;

		case CLOSE_ROTATION:
			return false;
			break;
		}

	}while(ActRotation == EMPTY_ROTATION);

	pOut->ClearStatusBar();

	return true;
}

bool RotateAction::Execute(){
	Output* pOut = pManager->GetOutput();

	if(pOut->get_zoom_factor() != 1)
		return false;

	if(ReadActionParameters()){
		pManager->Rotate(RotationalAngle);
		return true;
	}

	return false;
}
RotateAction::~RotateAction(void)
{
}
