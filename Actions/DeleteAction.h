#ifndef DELETE_ACTION_H
#define DELETE_ACTION_H

#include"Action.h"
#include "..\ApplicationManager.h"

class DeleteAction:public Action
{
public:
	DeleteAction(ApplicationManager *pApp);
	virtual bool ReadActionParameters();
	virtual bool Execute();
	~DeleteAction();
};

#endif