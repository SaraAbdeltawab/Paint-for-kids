#ifndef PASTE_ACTION_H
#define PASTE_ACTION_H

#include"Action.h"

class PasteAction:public Action
{
public:
	/*private:
	Point P; //clicked point*/
public:
	PasteAction(ApplicationManager *pApp);

	virtual bool ReadActionParameters();
	virtual bool Execute();
	~PasteAction();
};

#endif