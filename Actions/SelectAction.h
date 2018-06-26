#ifndef SELECT_ACTION_H
#define SELECT_ACTION_H
#include "Action.h"

class SelectAction:public Action
{
private:
	Point P; //clicked point

	void PrintFirstMsg() const;// it will be printed once 
public:

	SelectAction(ApplicationManager *pApp);	
	virtual bool ReadActionParameters();
	virtual bool Execute();
	~SelectAction();
};

#endif