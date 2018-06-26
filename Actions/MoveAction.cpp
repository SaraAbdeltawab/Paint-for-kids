#include "MoveAction.h"

#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"



MoveAction::MoveAction(ApplicationManager *pApp,CFigure * selected[],int count):Action(pApp)
{
	Selected=selected;
	this->count=count;

	saved = false;
}


bool MoveAction::ReadActionParameters()
{
	///5aly el return type boolean
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Click your destination point. ");
	pIn->GetPointClicked(Destination.x,Destination.y);
	if (!pOut->Check_Point(Destination))
		return false;
	pOut->ClearStatusBar();
	return true;
	
}
void MoveAction::GetTopLeft()
{
	Relative=Selected[0]->TopLeft();
	for (int i=1;i<count;i++)
	{
		Point temp=Selected[i]->TopLeft();
		if (temp.y<Relative.y)
			Relative=temp;
		else if (temp.y==Relative.y)
			if (temp.x<Relative.x)
				Relative=temp;
	}
}

void MoveAction::SetDirections()
{
	Left = (Destination.x<Relative.x) ? true:false;
	UP = (Destination.y<Relative.y) ? true:false;
	Sent.x =abs (Destination.x-Relative.x);
	Sent.y=abs(Destination.y-Relative.y);
}

bool MoveAction::CanMoveAll()const
{
	Output *pOut =pManager->GetOutput();
	for (int i=0;i<count;i++)
		if (!Selected[i]->CanMove(Sent,UP,Left,pOut))
			return false;
	return true;
}

void MoveAction::MoveAll()
{
	for (int i=0;i<count;i++)
		Selected[i]->Move(Sent,UP,Left);
}

bool MoveAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	if(pOut->get_zoom_factor() != 1)
		return false;
	if (count==0)
	{
		pOut->PrintMessage("There isn't any Selected Figure ,Please choose Select Action First");
		return false;
	}
	if(!ReadActionParameters())
	{
		pOut->PrintMessage("This is an Invalid destination point.");
		return false;
	}

	GetTopLeft();

	SetDirections();

	CanMove=CanMoveAll();

	if (CanMove)
	{
		MoveAll();
		return true;
	}
	else
	{
		pOut->PrintMessage("Can't move Selected Figure(s) to this destination point");
		return false;
	}
}