#ifndef CHANGE_FILL_CLR_ACTION_H
#define CHANGE_FILL_CLR_ACTION_H

#include "Action.h"

class ChangeFillClrAction :public Action
{
protected:
	color FillColor;
public:
	ChangeFillClrAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	void CheckFigures();
	virtual bool Execute() ;
	~ChangeFillClrAction(void);
};

#endif