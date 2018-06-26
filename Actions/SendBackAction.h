#ifndef SEND_BACK_ACTION_H
#define SEND_BACK_ACTION_H
#include"Action.h"

class SendBackAction:public Action
{
public:
	SendBackAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	virtual bool Execute();
	~SendBackAction();
};

#endif