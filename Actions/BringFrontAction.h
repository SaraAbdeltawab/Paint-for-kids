#ifndef BRING_FRONT_ACTION_H
#define BRING_FRONT_ACTION_H
#include"Action.h"

class BringFrontAction:public Action
{
public:
	BringFrontAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	virtual bool Execute();
	~BringFrontAction(void);
};

#endif
