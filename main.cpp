#include "ApplicationManager.h"

int main()
{

	ActionType ActType;
	//Create an object of ApplicationManager
	ApplicationManager AppManager;

	bool Executed;

	do
	{		
		//Read user action
		ActType = AppManager.GetUserAction();

		//Exexute the action
		Executed = AppManager.ExecuteAction(ActType);

		//Update the interface
		AppManager.UpdateInterface();	

	}while( !Executed || ActType != EXIT);
	

	
	return 0;
}

