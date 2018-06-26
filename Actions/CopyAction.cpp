#include "CopyAction.h"
#include "..\ApplicationManager.h"

CopyAction::CopyAction(ApplicationManager *pApp):Action(pApp)
{
	saved = false;
}

bool CopyAction::ReadActionParameters(){

	return true;
} 

bool CopyAction::Execute(){

	Output* pOut = pManager->GetOutput();

	if(pManager->getSelectedCount() == 0){
		pOut->PrintMessage("There isn't any Selected Figure ,Please choose Select Action First");
		return false;
	}

	if(pOut->get_zoom_factor() != 1)
		return false;

	pManager->Copy();
	pOut->PrintMessage("Copy selected figures");
	return true;

}
CopyAction::~CopyAction(void)
{}
