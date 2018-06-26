#ifndef SWITCH_TO_PLAY_ACTION_H
#define SWITCH_TO_PLAY_ACTION_H

#include"Action.h"

class SwitchToPlayAction:public Action
{
public:
	SwitchToPlayAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	virtual bool Execute();
	~SwitchToPlayAction();
};

#endif