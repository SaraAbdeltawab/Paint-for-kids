#pragma once
#include "Action.h"
 
class ZoomOutAction :public Action
{
	Point P;

public:

	ZoomOutAction(ApplicationManager *pApp);
	virtual bool ReadActionParameters();
	virtual bool Execute() ;
	~ZoomOutAction(void);
};

