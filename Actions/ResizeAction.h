#ifndef RESIZE_ACTION_H
#define RESIZE_ACTION_H

#include "Action.h"

class ResizeAction : public Action
{
private:
	float Factor;
public:
	
	ResizeAction(ApplicationManager *pApp);

	virtual bool ReadActionParameters();

	virtual bool Execute();


};

#endif