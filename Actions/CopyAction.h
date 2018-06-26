#ifndef COPY_ACTION_H
#define COPYACTION_H
#include"Action.h"

class CopyAction:public Action
{
public:
	CopyAction(ApplicationManager *pApp);
	virtual bool ReadActionParameters();
	virtual bool Execute();
	~CopyAction(void);
};

#endif