#ifndef LOAD_ACTION_H
#define LOAD_ACTION_H

#include "Action.h"
///// dol hna wla f el cpp ??
#include "..\Figures\CLine.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CTriangle.h"
#include "..\Figures\CCircle.h"
#include <fstream>
enum FigureType
{
	LINE,
	RECTANGLE,
	TRIANGLE,
	CIRCLE
}; ////////// da hna wla f el defs ??
class LoadAction  : public Action
{
private:
	ifstream InFile;
	string File_Name;
public:
	LoadAction(ApplicationManager *pApp);

	void Savegraph();
	virtual bool ReadActionParameters();
	void LoadAll();
	virtual bool Execute();

};

#endif