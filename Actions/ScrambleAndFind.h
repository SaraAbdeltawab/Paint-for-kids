#pragma once
#include "Action.h"
#include "../Figures/CFigure.h"

class ScrambleAndFind :public Action
{
private:

	int Valid,
		Invalid,
		count; //actual count
	CFigure** LeftFig;
	CFigure** RightFig;
public:
	ScrambleAndFind(ApplicationManager* pApp);
	virtual bool ReadActionParameters();
	void LeftGraph();
	void CreateBorder();
	void MoveRandomly();
	void RightGraph();
	void Delete(int index);
	void ShiftList(int index);
	void Play();
	void GameEnded();
	void UpdateInterface();
	void BringFront(int index);
	virtual bool Execute();
	~ScrambleAndFind();
};

