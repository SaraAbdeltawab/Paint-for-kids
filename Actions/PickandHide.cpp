#include "PickandHide.h"

#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"


PickandHide::PickandHide(ApplicationManager* pApp):Action(pApp)
{
	//pManager->DeleteAllList();
	pManager->CopyAllList();
	Valid=0;
	Invalid=0;
	SelectedPlay=NULL;
}

bool PickandHide::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->CreatePickAndHideSubMenu();
	pOut->PrintMessage("Pick and Hide : Choose the mode you want to pick with");

	do{

		Pick=pIn->GetUserPickChoice();

		switch (Pick)
		{
		case TYPE:
			break;

		case FILL_COLOR:
			break;

		case TYPE_AND_FILL_COLOR:
			break;

		case AREA:
			break;

		case CLOSE_PICK:
			pOut->ClearStatusBar();
			return false;
			break;

		}

	}while (Pick ==EMPTY_PICK);
	pOut->ClearStatusBar();
	pManager->UpdateInterface();
	return true;
}

void PickandHide::ExecuteType()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	Point P;
	pOut->PrintMessage("Pick by Type: Click the Type of Figure you want to pick");
	while (pManager->getFigCount() >0)
	{
		while (SelectedPlay == NULL)
		{
			///
			pIn->GetPointClicked(P.x,P.y);

			ActionType ActType = pIn->GetUserAction(P.x, P.y);
			if(ActType != DRAWING_AREA && ActType != STATUS && ActType != EMPTY)
			{
				pManager->SetWastedClick(P);
				return;
			}

			SelectedPlay = pManager->GetFigure(P);// This is the first figure selected in each punch of figures , based on this figure we calculate the valid and invalid
			Valid++;
		}
		string str= "Valid : " +to_string(Valid) +"     Invalid : " + to_string(Invalid);
		pOut->PrintMessage(str);
		pManager->SelectAllSameType(SelectedPlay);// we put the figures with the same properties in the selected array to loop on it instead of looping on the whole array
		pManager->Delete(SelectedPlay); // we delete the first selected figure ,, as it is valid 
		SelectedPlay=NULL;
		pManager->BringFront(); 
		pManager->UpdateInterface();
		while ( pManager->getSelectedCount() >0)
		{
			pIn->GetPointClicked(P.x,P.y);
			ActionType ActType = pIn->GetUserAction(P.x, P.y);
			if(ActType != DRAWING_AREA && ActType != STATUS && ActType != EMPTY)
			{
				pManager->SetWastedClick(P);
				return;
			}
			SelectedPlay = pManager->GetFigure(P);
			if (SelectedPlay !=NULL)
			{
				if(pManager->FoundInSelected(SelectedPlay))
				{
					/// if the figure is found in the selected array then it is a valid choice so we remove it from the selected and delete it 
					Valid++;
					pManager->RemoveFromSelected(SelectedPlay);
					pManager->Delete(SelectedPlay);
					SelectedPlay=NULL;
				}
				else
					Invalid++;
			}
			str= "Valid : " +to_string(Valid) +"     Invalid : " + to_string(Invalid);
			pOut->PrintMessage(str);
			pManager->UpdateInterface();
		}
	}
	string s="The Game is Over , You Grade is "+to_string ((float)(1.0*Valid/(Valid+Invalid)));
	pOut->PrintMessage(s);
}

void PickandHide:: ExecuteFillColor()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	Point P;
	pOut->PrintMessage("Pick by Fill Color: Click the Figure with the Fill color you want to pick");
	while (pManager-> getFigCount() >0)
	{
		while (SelectedPlay ==NULL)
		{
			///
			pIn->GetPointClicked(P.x,P.y);
			ActionType ActType = pIn->GetUserAction(P.x, P.y);
			if(ActType != DRAWING_AREA && ActType != STATUS && ActType != EMPTY)
			{
				pManager->SetWastedClick(P);
				return;
			}
			SelectedPlay = pManager->GetFigure(P); // This is the first figure selected in each punch of figures , based on this figure we calculate the valid and invalid
			Valid++;
		}
		string str= "Valid : " +to_string(Valid) +"     Invalid : " + to_string(Invalid);
		pOut->PrintMessage(str);
		pManager->SelectAllSameFillColor(SelectedPlay); // we put the figures with the same properties in the selected array to loop on it instead of looping on the whole array
		pManager->Delete(SelectedPlay); // we delete the first selected figure ,, as it is valid 
		SelectedPlay=NULL;
		pManager->BringFront(); // bring front all selected ,, so that the kid can see them and select them
		pManager->UpdateInterface();
		while ( pManager->getSelectedCount() >0)
		{
			pIn->GetPointClicked(P.x,P.y);
			ActionType ActType = pIn->GetUserAction(P.x, P.y);
			if(ActType != DRAWING_AREA && ActType != STATUS && ActType != EMPTY)
			{
				/// if anotther action is selected we set the wasted click and end the game
				pManager->SetWastedClick(P);
				return;
			}
			SelectedPlay = pManager->GetFigure(P);
			if (SelectedPlay !=NULL)
			{
				if(pManager->FoundInSelected(SelectedPlay))
				{
					/// if the figure is found in the selected array then it is a valid choice so we remove it from the selected and delete it 
					Valid++;
					pManager->RemoveFromSelected(SelectedPlay);
					pManager->Delete(SelectedPlay);
					SelectedPlay=NULL;
				}
				else
					Invalid++;
			}
			str= "Valid : " +to_string(Valid) +"     Invalid : " + to_string(Invalid);
			pOut->PrintMessage(str);
			pManager->UpdateInterface();
		}
	}
	string s="The Game is Over , You Grade is "+to_string ((float)(1.0*Valid/(Valid+Invalid)));
	pOut->PrintMessage(s);
}

void PickandHide::ExecuteTypeAndFillColor()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	Point P;
	pOut->PrintMessage("Pick by Type and Fill Color: Click the Type  Figure with the color you want to pick");
	while (pManager-> getFigCount() >0)
	{
		while (SelectedPlay ==NULL)
		{
			/////
			pIn->GetPointClicked(P.x,P.y);
			ActionType ActType = pIn->GetUserAction(P.x, P.y);
			if(ActType != DRAWING_AREA && ActType != STATUS && ActType != EMPTY)
			{
				pManager->SetWastedClick(P);
				return;
			}
			SelectedPlay = pManager->GetFigure(P); // This is the first figure selected in each punch of figures , based on this figure we calculate the valid and invalid
			Valid++;
		}
		string str= "Valid : " +to_string(Valid) +"     Invalid : " + to_string(Invalid);
		pOut->PrintMessage(str);
		pManager->SelectAllSameTypeAndFillColor(SelectedPlay);// we put the figures with the same properties in the selected array to loop on it instead of looping on the whole array
		pManager->Delete(SelectedPlay); // we delete the first selected figure ,, as it is valid 
		SelectedPlay=NULL;
		pManager->BringFront(); 
		pManager->UpdateInterface();
		while ( pManager->getSelectedCount() >0)
		{
			pIn->GetPointClicked(P.x,P.y);
			ActionType ActType = pIn->GetUserAction(P.x, P.y);
			if(ActType != DRAWING_AREA && ActType != STATUS && ActType != EMPTY)
			{
				pManager->SetWastedClick(P);
				return;
			}
			SelectedPlay = pManager->GetFigure(P);
			if (SelectedPlay !=NULL)
			{
				if(pManager->FoundInSelected(SelectedPlay))
				{
					/// if the figure is found in the selected array then it is a valid choice so we remove it from the selected and delete it 
					Valid++;
					pManager->RemoveFromSelected(SelectedPlay);
					pManager->Delete(SelectedPlay);
					SelectedPlay=NULL;
				}
				else
					Invalid++;
			}
			str= "Valid : " +to_string(Valid) +"     Invalid : " + to_string(Invalid);
			pOut->PrintMessage(str);
			pManager->UpdateInterface();
		}
	}
	string s="The Game is Over , You Grade is "+to_string ((float)(1.0*Valid/(Valid+Invalid)));
	pOut->PrintMessage(s);
}

void PickandHide:: ExecuteArea()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	Point P;
	pOut->PrintMessage("Pick by Area : Select Figures With Descending order ");
	pManager->SortPlayListWithArea(); // we sort the play list assending to make them be drawn descengingly as the last figures are drawn last(ubove the others) 
	pManager->UpdateInterface(); // to draw the figures in their order 
	while (pManager-> getFigCount() >0)
	{
		pManager->SelectAllSameLargestArea(); // if there are some figures with the same area put them in the selected array ,, so that he can choose any of them
		while ( pManager->getSelectedCount() >0)
		{
			pIn->GetPointClicked(P.x,P.y);
			ActionType ActType = pIn->GetUserAction(P.x, P.y);
			if(ActType != DRAWING_AREA && ActType != STATUS && ActType != EMPTY)
			{
				pManager->SetWastedClick(P);
				return;
			}
			SelectedPlay = pManager->GetFigure(P);
			if (SelectedPlay !=NULL)
			{
				if(pManager->FoundInSelected(SelectedPlay))
				{
					/// if the figure is found in the selected array then it is a valid choice so we remove it from the selected and delete it 
					Valid++;
					pManager->RemoveFromSelected(SelectedPlay);
					pManager->Delete(SelectedPlay);
					SelectedPlay=NULL;
				}
				else
					Invalid++;

			}
			string str= "Valid : " +to_string(Valid) +"     Invalid : " + to_string(Invalid);
			pOut->PrintMessage(str);
			pManager->UpdateInterface();
		}
	}
	string s="The Game is Over , You Grade is "+to_string ((float)(1.0*Valid/(Valid+Invalid)));
	pOut->PrintMessage(s);
}
bool PickandHide::Execute()
{
	if(ReadActionParameters())
	{
		if (pManager-> getFigCount()>0)
		{
			switch (Pick)
			{
			case TYPE:
				ExecuteType();
				break;

			case FILL_COLOR:
				ExecuteFillColor();
				break;

			case TYPE_AND_FILL_COLOR:
				ExecuteTypeAndFillColor();
				break;

			case AREA:
				ExecuteArea();
				break;
			// already checked if he closed or not in read parameters so no need to check agains

			}
			return true;
		}
		Output *pOut =pManager->GetOutput();
		/// the figure count is zaeo so he needs to draw figures first
		pOut->PrintMessage("Switch To Draw Mode to draw some figures , then come back again to play");
	}
	return true;
}

PickandHide::~PickandHide()
{
	pManager->DeleteAllList();
}
