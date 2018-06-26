#ifndef MOVE_ACTION_H
#define MOVE_ACTION_H

#include "Action.h"
#include "..\Figures\CFigure.h"

class MoveAction : public Action
{
private:
	Point Destination;
	Point Relative;
	Point Sent;
	bool UP;
	bool Left;
	bool CanMove;
	CFigure **Selected;
	int count;

public:

	MoveAction(ApplicationManager *pApp,CFigure * selected[],int count);

	virtual bool ReadActionParameters();

	void GetTopLeft();

	void SetDirections();

	bool CanMoveAll()const;

	void MoveAll();

	virtual bool Execute();

};
#endif