#ifndef ADD_CIRC_ACTION_H
#define ADD_CIRC_ACTION_H

#include "Action.h"

//Add Circle Action class
class AddCircAction: public Action
{
private:

	Point P1, P2;  //2 points read from user
	int Radius;
	GfxInfo CircGfxInfo; //Figure graphis info
	bool Check_Radius() const;

public:

	AddCircAction(ApplicationManager *pApp);
	int CalculateRadius()const; //To calculate the radius of the circle

	//Reads circle parameters
	virtual bool ReadActionParameters();
	//Add circle to the ApplicationManager
	virtual bool Execute() ;
	
};

#endif

