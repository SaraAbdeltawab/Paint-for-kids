#pragma once
#include "Action.h"
class ZoomInAction : public Action
{
	Point P;
public:
	ZoomInAction(ApplicationManager *pApp);
	virtual bool ReadActionParameters();
	virtual bool Execute() ;
	~ZoomInAction(void);
};

