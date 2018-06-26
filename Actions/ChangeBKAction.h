#ifndef CHANGE_BK_ACTION_H
#define CHANGE_BK_ACTION_H

#include "Action.h"

class ChangeBKAction:public Action
{
protected:
	color UserColor;
public:
	ChangeBKAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	virtual bool Execute() ;
	~ChangeBKAction(void);
};

#endif