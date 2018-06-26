#ifndef SWITCH_TO_DRAW_ACTION_H
#define SWITCH_TO_DRAW_ACTION_H

#include"Action.h"

class SwitchToDrawAction:public Action
{
public:
	SwitchToDrawAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	virtual bool Execute();
	~SwitchToDrawAction();
};

#endif