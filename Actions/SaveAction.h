#ifndef SAVE_ACTION_H
#define SAVE_ACTION_H

#include "Action.h"
#include <fstream>
class SaveAction  : public Action
{
private:
	ofstream OutFile;
	string File_Name;
public:
	SaveAction(ApplicationManager *pApp);

	bool Check_File_Name(string s);

	virtual bool ReadActionParameters();

	virtual bool Execute();



};
#endif