#include "ResizeAction.h"

#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"


ResizeAction::ResizeAction(ApplicationManager *pApp):Action(pApp)
{
	saved = false;
}

bool ResizeAction::ReadActionParameters()
{

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	if(pManager->getSelectedCount() == 0){
		pOut->PrintMessage("There isn't any Selected Figure ,Please choose Select Action First");
		return false;
	}

	ResizeFactor Res;
	pOut->CreateResizeSubMenu();
	pOut->PrintMessage("Choose the Resize Factor");
	do{

		Res=pIn->GetUserResizeFactor();

		switch (Res)
		{
		case QUARTER:
			Factor=0.25;
			break;

		case HALF:
			Factor=0.5;
			break;

		case BYTWO:
			Factor=2.0;
			break;

		case BYFOUR:
			Factor=4.0;
			break;

		case CLOSE_RESIZE:
			return false;
			break;

		}

	}while (Res ==EMPTY_RESIZE);
	pOut->ClearStatusBar();
	return true;
}

bool ResizeAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	if(ReadActionParameters()){
		pManager->Resize(Factor);
		return true;
	}

	return false;
}