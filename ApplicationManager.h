#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures ////hwa eh dah bzbt ?! enum leeh !!!

private:

	int FigCount;		//Actual number of figures
	int ClipboardCount;
	int SelectedCount;

	//Lists
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	CFigure* Clipboard[MaxFigCount]; //List of (Cut/Copy)Figures to be pasted
	CFigure* Selected[MaxFigCount]; //List of selected figures

	//Play mode
	int PlayCount;
	int Selectedplaycount;

	CFigure* PlayList[MaxFigCount];
	CFigure* SelectedPlay [MaxFigCount];

	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

	bool wastedset; // to check if there is a wasted click or not
	Point WastedClick ; // if we want to execute an action from another action 

public:	

	ApplicationManager(); 
	~ApplicationManager();

	// -- Action-Related Functions
	ActionType GetUserAction() const;//Reads the input command from the user and returns the corresponding action type
	bool ExecuteAction(ActionType) ; //Creates an action and executes it

	// -- Figures Management Functions
	void AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	CFigure *GetFigure(Point P) const; //Search for a figure given a point inside the figure

	void SaveAll(ofstream &OutFile)const; //Save all drawn figures in a file
	void Load(ifstream &Infile);
	CFigure** CopyAll(); //Copy all Figlist to be used in play mode
	void Copy(); //Copy all selected figures
	void Cut(); //Cut all selected figures
	void Delete(); //Delete all selected Figures
	void Delete (CFigure *pfig); /// Overloading to be used in play mode
	void Paste(); //Paste all figures in the clipboard
	void Zooming(float ); //Zoom the graph with the zooming factor
	/**/void Resize(float Factor); //Resize selected Figues by a resize factor
	void Rotate(int RotationalAngle); //Rotate all selected figures 
	void BringFront(); //Bring all selected figure front 
	void SendBack(); //Send all selected figurs back

	void ShiftFiglistDown(CFigure*); 
	void ShiftFiglistUp(CFigure*);
	void ShiftSelectedlistDown(int);
	void ShiftSelectedlistUp(int);
	/*call in destractour*/void ClearClipboard(); //Remove all figures from the clipboard

	void AddInClipboard(CFigure* pFig);
	void AddInSelected(CFigure* pFig);
	void RemoveFromSelected(CFigure* pFig);

	void DeleteAllList(); /// Delete all the lists (fig list & clip board ---> in draw mode)
	//                        (play list ----> in play mode)

	bool ChangeBorderWidth(int width);
	//-- Changing Colors
	bool ChangeDrawClr(color);
	bool ChangeFillClr(color);

	int getFigCount() const;
	int getSelectedCount() const;
	int getClipboardCount() const;

	/**///Play Mode
	void SelectAllSameType(CFigure *pfig); //Pick by type
	void SelectAllSameFillColor(CFigure * pfig); //Pick by fillcolor
	void SelectAllSameTypeAndFillColor(CFigure * pfig); //Pick by type and fillcolor
	void SelectAllSameLargestArea(); // Assumes that array is soted ascendingly

	void SortPlayListWithArea(); //Sort play list ascendingly
	void CopyAllList(); /// copy all the fig list to the play list for play mode

	/*?*/bool FoundInSelected(CFigure *pfig); //l el play mode f pick and hide 

	//Point defualtWasted(); // sets the wasted click to its defualt value
	void SetWastedClick(Point Click); //to be used in play mode if the user want to start a game while playing

	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output

	void UpdateInterface() const;	//Redraws all the drawing window
	void UpdateInterface(CFigure**, int Size ) const;	//overloading ...Redraws all the drawing window

};

#endif