#include "LoadAction.h"

#include "..\ApplicationManager.h"


LoadAction::LoadAction(ApplicationManager*pApp):Action (pApp)
{}

void LoadAction::Savegraph()
{
	if(pManager->getFigCount()>0)
	{
		Output* pOut = pManager->GetOutput();
		Input* pIn = pManager->GetInput();
		string str;
		pOut->PrintMessage("Do you want to save the existing gragh ? If yes please press 'y' If no press any other key.");
		str=pIn->GetSrting(pOut);
		if (str=="y")
			pManager->ExecuteAction(SAVE);
	}
}


bool LoadAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	string str;

	pOut->PrintMessage("Load graph : Please enter a saved file name.");

	str = pIn->GetSrting(pOut);
	str+=".txt";
	InFile.open(str,ios::in);
	if (!InFile.is_open())
		return false;
	File_Name=str;
	pOut->ClearStatusBar();
	return true;
}

void LoadAction::LoadAll()
{
	pManager->Load(InFile);
	int Figno ;
	InFile>>Figno;
	for (int i=0;i<Figno;i++)
	{
		int x;
		CFigure *C;
		InFile>>x;
		FigureType F =(FigureType)x;
		switch (F)
		{
		case LINE:
			C= new CLine ();
			break;

		case RECTANGLE:
			C=new CRectangle ();
			break;

		case TRIANGLE:
			C=new CTriangle ();
			break;

		case CIRCLE:
			C=new CCircle ();
			break;
		default:
			break;
		}
		C->Load(InFile);
		pManager->AddFigure(C);
	}
}

bool LoadAction::Execute()
{
	Savegraph(); 
	Output *pOut=pManager->GetOutput();
	if (!ReadActionParameters())
	{
		pOut->PrintMessage("ERROR! There isn't a file with this name");
		return false;
	}
	pManager->DeleteAllList();
	LoadAll();
	InFile.close();
	return true;
}