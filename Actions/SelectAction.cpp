#include "SelectAction.h"
#include "..\ApplicationManager.h"


SelectAction::SelectAction(ApplicationManager *pApp):Action(pApp)
{
}

void SelectAction::PrintFirstMsg() const{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Select the required Figures, When finished click on the select icon");
}
bool SelectAction::ReadActionParameters(){

	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Read the coordinate of point clicked 
	pIn->GetPointClicked(P.x, P.y);

	/*ActionType Click = pIn->GetUserAction(P.x, P.y); 
	if( Click != DRAWING_AREA && Click != STATUS){
	pManager->ExecuteAction(Click);              
	return false;
	}*/

	if(pIn->CheckPointOnSelectIcon(P)){

		int SelectedCount = pManager->getSelectedCount();
		string str = " Number of Selected Figures = " + to_string(SelectedCount);
		pOut->PrintMessage(str);
		return false;
	}

	float zoom = pOut->get_zoom_factor();
	Point center = pOut->get_zoom_center();
	P.x = (int)((P.x-center.x)/zoom + center.x);
	P.y = (int)((P.y-center.y)/zoom + center.y);
	pOut->ClearStatusBar();

	return true;
}

bool SelectAction::Execute()
{ 
	PrintFirstMsg();
	Output* pOut = pManager->GetOutput();
	while(ReadActionParameters()){

		CFigure* pFig = pManager->GetFigure(P);
		if(pFig != NULL){
			if(pFig->IsSelected()){
				pFig->SetSelected(false);
				pManager->RemoveFromSelected(pFig);
			}
			else{
				pManager->AddInSelected(pFig);
				pFig->SetSelected(true);
				pFig->PrintInfo(pOut);
			}

			pManager->UpdateInterface();  //To appear the selected fig once the user selected it
		}

		else	pOut->PrintMessage("Selection Mode, Click on the select icon to finish");
	}
	return true;
}

SelectAction::~SelectAction()
{
}
