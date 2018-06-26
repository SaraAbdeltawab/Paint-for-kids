#ifndef ROTATE_ACTION_H
#define ROTATE_ACTION_H
#include"Action.h"

class RotateAction:public Action
{
private:
	int RotationalAngle;
public:
	RotateAction(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	virtual bool Execute();
	~RotateAction();
};

#endif
