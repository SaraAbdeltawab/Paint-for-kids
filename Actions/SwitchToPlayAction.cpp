#include "SwitchToPlayAction.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

SwitchToPlayAction::SwitchToPlayAction(ApplicationManager* pApp):Action(pApp)
{
}

bool SwitchToPlayAction::ReadActionParameters()
{
	return true;
}

bool SwitchToPlayAction::Execute()
{
	Output *pOut=pManager->GetOutput();
	if(pOut->get_zoom_factor() != 1) // not a valid action when the graph zoomed 
		return false;
	pOut->CreatePlayToolBar(); // it creates the play tool bar and sets the ui mode to play mode
	pManager->CopyAllList(); // we copy the figure list into the play list 
	pOut->PrintMessage("Play Mode , Please Choose the game you want to play from the tool bar"); 
	return true;
}

SwitchToPlayAction::~SwitchToPlayAction()
{
}
