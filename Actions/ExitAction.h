#ifndef EXIT_ACTION_H
#define EXIT_ACTION_H

#include "Action.h"

class ExitAction: public Action
{
	Point P; //clicked point
public:
	ExitAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	virtual bool Execute();
	~ExitAction();
};

#endif