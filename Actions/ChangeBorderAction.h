#ifndef CHANGE_BORDER_ACTION_H
#define CHANGE_BORDER_ACTION_H
#include "Action.h"

class ChangeBorderAction: public Action
{
private:
	int BorderWidth;
public:
	ChangeBorderAction(ApplicationManager* pApp);
	bool ReadActionParameters();
	bool Execute();
	~ChangeBorderAction();
};

#endif