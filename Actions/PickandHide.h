#ifndef PICK_AND_HIDE_H
#define PICK_AND_HIDE_H

#include "Action.h"
#include "..\Figures\CFigure.h"

class PickandHide : public Action
{
private:
	PickChoices Pick;
	// a3ml figure wa7d asmeh,, a5leh b null bardo f el constrctor ,, w kol mara ya amsa7o mn el list w azwd el valid ya 2ma a5leh null tani a azwd el invalid 
	CFigure * SelectedPlay;
	int Valid;
	int Invalid;
public:
	
	PickandHide(ApplicationManager *pApp);

	virtual bool ReadActionParameters();

	virtual bool Execute();

	void ExecuteType();
	void ExecuteFillColor();
	void ExecuteTypeAndFillColor();
	void ExecuteArea();
	
	~PickandHide();
};

#endif