#include "ScrambleAndFind.h"
#include "../ApplicationManager.h"
#include "../Figures/CLine.h"
#include <random>

ScrambleAndFind::ScrambleAndFind(ApplicationManager* pApp):Action(pApp)
{
	Valid = 0;
	Invalid = 0;
	//pManager->DeleteAllList(); 
	pManager->CopyAllList();
	count = pManager->getFigCount();  
	LeftFig = pManager->CopyAll();
	RightFig = new CFigure*[count];
}

void ScrambleAndFind::RightGraph()
{

	for(int i=0;i<count;i++)
	{
		RightFig[i] = LeftFig[i]->Copy();
	}
}
void ScrambleAndFind::Play()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	Point p;
	bool check;
	string msg;

	pOut->PrintMessage("Find the selected figure");

	while( count != 0)
	{
		check = false;
		int index = rand()% count;

		LeftFig[index]->SetSelected(true);
		BringFront(index);
		index = count-1; //as it is brought front

		UpdateInterface();  //To appear the selected fig once it is selected 

		

		while(!check){

			pIn->GetPointClicked(p.x, p.y);

			ActionType ActType = pIn->GetUserAction(p.x, p.y);

			if(ActType != DRAWING_AREA && ActType != STATUS && ActType != EMPTY){
				pManager->SetWastedClick(p);
				return;
			}


			check =	RightFig[index]->CheckPointFound(p);

			if(check){
				Delete(index);
				UpdateInterface();
				Valid++;
				msg = "Valid : " +to_string(Valid) +"     Invalid : " + to_string(Invalid);
				pOut->PrintMessage(msg);
				break;
			}

			else{
				 msg = "Valid : " +to_string(Valid) +"     Invalid : " + to_string(Invalid);
				pOut->PrintMessage(msg);
				Invalid++;
			}

		}

	}
}

void ScrambleAndFind::GameEnded(){

	Output* pOut = pManager->GetOutput();
	string msg = "The Game is Over , You Grade is "+to_string ((float)(1.0*Valid/(Valid+Invalid)));
	pOut->PrintMessage(msg);

}

void ScrambleAndFind::Delete(int index){

	delete RightFig[index];
	delete LeftFig[index];
	RightFig[index] = NULL;
	LeftFig[index] = NULL;
	ShiftList(index);
	count--;
}

void ScrambleAndFind::ShiftList(int index){

	for(;index<count-1;index++){
		LeftFig[index] = LeftFig[index+1];
		RightFig[index] = RightFig[index+1];
	}

	LeftFig[index] = NULL;
	RightFig[index] = NULL;
}

void ScrambleAndFind::MoveRandomly()
{
	Output*pOut = pManager->GetOutput();
	Point randp; Point Mostleft;Point added;
	int i=0;
	int UIwidth = pOut->getUIWidth();
	int UIheight = pOut->getUIHeight();

	while(i<count)
	{
		randp.x=rand()%UIwidth + 17+ ((UIwidth+1)/2); //17 : bec of the used library
		randp.y=rand()%(UIheight - pOut->getUIStatusbarHeight()) + pOut->getUIToolbarHeight();
		Mostleft = RightFig[i]->MostLeft();
		added.x = randp.x-Mostleft.x; 
		added.y = randp.y-Mostleft.y;

		if(RightFig[i]->CanMove(added,true,false,pOut)){
			RightFig[i]->Move(added,true,false);
			i++;
		}
		else if(RightFig[i]->CanMove(added,false,false,pOut)){
			RightFig[i]->Move(added,false,false);            
			i++;
		}
	}
}
void ScrambleAndFind::LeftGraph()
{
	Point p;
	Output* pOut = pManager->GetOutput();
	pOut->ClearDrawArea();
	for(int i =0;i<count ;i++)
	{
		LeftFig[i]->Resize(0.5);
		p.x = (LeftFig[i]->TopLeft().x+1)/2;   p.y = 0;
		LeftFig[i]->Move(p, true, true);
	}
}

bool ScrambleAndFind::ReadActionParameters()
{
	return true;
}

//works for left and right FigLists
void ScrambleAndFind::BringFront(int index){

	CFigure* LeftpFig = LeftFig[index];
	CFigure* RightpFig = RightFig[index];

	ShiftList(index);

	LeftFig[count-1] = LeftpFig;
	RightFig[count-1] = RightpFig;
}

bool ScrambleAndFind::Execute()
{
	Output* pOut = pManager->GetOutput();
	if(count == 0){
		pOut->PrintMessage("Switch To Draw Mode to draw some figures , then come back again to play");
		return false;
	}
	LeftGraph();
	RightGraph();
	MoveRandomly();
	UpdateInterface();
	Play();
	GameEnded();
	return true;

}

void ScrambleAndFind::UpdateInterface(){ 

	Output* pOut = pManager->GetOutput();

	pOut->ClearDrawArea();

	pManager->UpdateInterface(LeftFig, count);
	pManager->UpdateInterface(RightFig, count);

	pOut->CreateBorder();

}
ScrambleAndFind::~ScrambleAndFind(void)
{
	for(int i=0;i<count;i++)
	{
		delete LeftFig[i];
		delete RightFig[i];
	}

	delete[]LeftFig;
	delete[]RightFig;

	LeftFig = NULL;
	RightFig = NULL;
	pManager->DeleteAllList();
}
