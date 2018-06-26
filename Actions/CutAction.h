#ifndef CUT_ACTION_H
#define CUT_ACTION_H
#include"Action.h"
class CutAction:public Action
{
private:

public:
	CutAction(ApplicationManager *pApp);
	virtual bool ReadActionParameters();
	virtual bool Execute();
	~CutAction();
};

#endif