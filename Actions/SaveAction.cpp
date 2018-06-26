#include "SaveAction.h"

#include "..\ApplicationManager.h"



SaveAction::SaveAction(ApplicationManager *pApp):Action(pApp)
{
	saved = true;
}

bool SaveAction::Check_File_Name(string s)
{
	/// This function checks whether  we can create a file with the name give or not
	char arr[]={'\\' , '/' ,':','*','?','"','<','>','|'};
	for(int i=0;i<9;i++)
	{
		int idx=s.find(arr[i]);
		if(idx !=-1)
			return false;
	}
	return true;
}

bool SaveAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	string str;
	do
	{
	pOut->PrintMessage("Save graph : Please enter the file name. NOTE:file name can't contain \\/:*?\"<>|");/// escpape quote\"

	str = pIn->GetSrting(pOut);
	pOut->ClearStatusBar();
	}while (!Check_File_Name(str));

	File_Name=str+=".txt"; // we add ehe extention to the user's file name
	pOut->ClearStatusBar();
	return true;
}

bool SaveAction::Execute()
{
	ReadActionParameters();
	OutFile.open(File_Name,ios::out);
	pManager->SaveAll(OutFile);
	OutFile.close();
	return true;
}
