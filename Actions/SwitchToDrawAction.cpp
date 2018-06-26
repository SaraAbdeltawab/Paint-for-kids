#include "SwitchToDrawAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

SwitchToDrawAction::SwitchToDrawAction(ApplicationManager* pApp):Action(pApp)
{
}

bool SwitchToDrawAction::ReadActionParameters()
{
	return true;
}

bool SwitchToDrawAction::Execute()
{
	Output *pOut=pManager->GetOutput();
	pManager->DeleteAllList(); // this is to delete the play list as we finished playing
	pOut->CreateDrawToolBar(); // this creates the draw toolbar and sets the i mode to draw mode so we are back to our essential arrays
	pOut->PrintMessage("Draw mode"); 
	pOut->ClearStatusBar(); 
	return true;
}

SwitchToDrawAction::~SwitchToDrawAction()
{
}
