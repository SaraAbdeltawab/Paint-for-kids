#ifndef ADD_LINE_ACTION_H
#define ADD_LINE_ACTION_H

#include "Action.h"


class AddLineAction:public Action
{
private:
	Point P1, P2; // start & end point
	GfxInfo LineGfxInfo;

public:
	AddLineAction(ApplicationManager *pApp);

	//Reads line parameters
	virtual bool ReadActionParameters();
	
	//Add line to the ApplicationManager
	virtual bool Execute() ;
	
};
#endif
