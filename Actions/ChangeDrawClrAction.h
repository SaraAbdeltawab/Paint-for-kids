#ifndef CHANGE_DRAW_CLR_ACTION_H
#define CHANGE_DRAW_CLR_ACTION_H
#include "Action.h"
class ChangeDrawClrAction:public Action
{
protected:
	color DrawColor;
public:
	ChangeDrawClrAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	void CheckFigures();
	virtual bool Execute() ;
	~ChangeDrawClrAction(void);
};

#endif