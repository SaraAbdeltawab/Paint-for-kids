#include "PasteAction.h"
#include "..\ApplicationManager.h"

PasteAction::PasteAction(ApplicationManager *pApp):Action(pApp)
{
	saved = false;
}

bool PasteAction::ReadActionParameters(){
	return true;
}

bool PasteAction::Execute()
{

	Output* pOut = pManager->GetOutput();

	if(pManager->getClipboardCount() == 0){
		pOut->PrintMessage("There isn't any Figure In Clipoard");
		return false;
	}

	if(pOut->get_zoom_factor() != 1)
		return false;
	
	pManager->Paste();
	return true;

}

PasteAction::~PasteAction()
{
}
