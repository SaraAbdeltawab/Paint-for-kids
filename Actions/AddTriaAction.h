#ifndef ADD_TRIA_ACTION_H
#define ADD_TRIA_ACTION_H

#include "Action.h"

class AddTriaAction: public Action
{
private:
	Point P1, P2, P3; 
	GfxInfo TriaGfxInfo;

public:
	AddTriaAction(ApplicationManager *pApp);
	//Reads triangle parameters
	virtual bool ReadActionParameters();
	
	//Add triangle to the ApplicationManager
	virtual bool Execute() ;
	~AddTriaAction();
};

#endif