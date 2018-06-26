#include "ApplicationManager.h"
#include "Actions\AllActionIncludes.h"
#include <algorithm>
using namespace std;

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	FigCount = 0;
	ClipboardCount = 0;
	SelectedCount=0;
	PlayCount=0;
	Selectedplaycount=0;

	//Set all arrays to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	

	for(int i=0; i<MaxFigCount; i++)
		Clipboard[i] = NULL;	

	for(int i=0; i<MaxFigCount; i++)
		Selected[i] = NULL;	

	/**/for(int i=0; i<MaxFigCount; i++)
		PlayList[i] = NULL;	

	/**/for (int i=0;i<MaxFigCount;i++)
		SelectedPlay[i] =NULL;

	wastedset=false;
	//WastedClick=defualtWasted(); // sets the wastes click to its defualt value;
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
bool ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;

	//According to Action Type, create the corresponding action object
	switch (ActType)
	{

	case DRAW_RECT:
		pAct = new AddRectAction(this);
		break;

	case DRAW_TRI:
		pAct = new AddTriaAction(this);
		break;

	case DRAW_LINE:
		pAct = new AddLineAction(this);
		break;

	case DRAW_CIRC:
		pAct= new AddCircAction(this);
		break;

	case BRD_DRAW_WID:
		pAct = new ChangeBorderAction(this);
		break;

	case CHNG_BK_CLR:
		pAct = new ChangeBKAction(this);
		break;

	case CHNG_DRAW_CLR:
		pAct= new ChangeDrawClrAction(this);
		break;

	case CHNG_FILL_CLR:
		pAct= new ChangeFillClrAction(this);
		break;

	case SAVE:
		pAct=new SaveAction(this);
		break;

	case LOAD:
		pAct=new LoadAction(this);
		break;

	case SELECT:
		pAct= new SelectAction(this);
		break;

	case COPY:
		pAct = new CopyAction(this);
		break;

	case CUT:
		pAct = new CutAction(this);
		break;

	case PASTE:
		pAct=new PasteAction(this);
		break;

	case DEL:
		pAct = new DeleteAction(this);
		break;

	case MOVE:
		pAct = new MoveAction(this,Selected,SelectedCount);
		break;

	case RESIZE:
		pAct = new ResizeAction(this);
		break;

	case ZOOM_IN:
		pAct = new ZoomInAction(this);
		break;

	case ZOOM_OUT:
		pAct = new ZoomOutAction(this);
		break;

	case ROTATE:
		pAct = new RotateAction(this);
		break;

	case BRNG_FRNT:
		pAct = new BringFrontAction(this);
		break;

	case SEND_BACK:
		pAct = new SendBackAction(this);
		break;

	case TO_PLAY:
		pAct = new SwitchToPlayAction(this); 
		break;

	case EXIT:
		pAct= new ExitAction(this);
		break;

	case SCRAMBLE_AND_FIND:
		pAct= new ScrambleAndFind(this);
		break;

	case PICK_AND_HIDE:
		pAct=new PickandHide(this);
		break;

	case TO_DRAW:
		pAct=new SwitchToDrawAction(this);
		break;

	case STATUS:	//a click on the status bar ==> no action
		return true ;
	}

	bool Executed = false; //initialization

	//Execute the created action
	if(pAct != NULL)
	{
		Executed=pAct->Execute();//Execute
		////
		//ExecuteAction(WastedClick);
		delete pAct;	//Action is not needed any more ==> delete it
		pAct = NULL;
		if (wastedset)
		{
			wastedset=false;
			ExecuteAction(pIn->GetUserAction(WastedClick.x,WastedClick.y));
			//WastedClick=defualtWasted();
		}
	}

	return Executed;
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (pOut->get_Mode()==MODE_DRAW)
	{
		if(FigCount < MaxFigCount )
			FigList[FigCount++] = pFig;	
	}
	else
	{
		if (PlayCount < MaxFigCount)
			PlayList[PlayCount++]=pFig;
	}
}

/////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::ClearClipboard(){

	for(int i = 0; i<ClipboardCount; i++){
		if(Clipboard[i] != NULL){
			delete Clipboard[i];
			Clipboard[i] = NULL;
		}
		else  break;
	}
	ClipboardCount = 0;

}
///////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::AddInClipboard(CFigure* pFig){

	pFig->SetSelected(true); //as we want the clipboard to be selected the user may want to make some operation on it
	if(ClipboardCount < MaxFigCount )
		Clipboard[ClipboardCount++] = pFig;	
}

////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::AddInSelected(CFigure* pFig)
{
	if (pOut->get_Mode()==MODE_DRAW)
		Selected[SelectedCount++] = pFig;

	//play mode
	else 
		SelectedPlay[Selectedplaycount++] = pFig;

}

void ApplicationManager::RemoveFromSelected(CFigure* pFig)
{

	if (pOut->get_Mode()==MODE_DRAW)
	{
		int i = 0;
		while(Selected[i] != pFig){i++;}  //get the index of the removed figure

		ShiftSelectedlistDown(i);
		pFig = NULL;
	}

	//Play mode
	else
	{
		int i = 0;
		while(SelectedPlay[i] != pFig){i++;}  //get the index of the removed figure

		ShiftSelectedlistDown(i);
		pFig = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager:: SelectAllSameType(CFigure* pfig)
{
	// we fisrt want to know what is the type of the given figure
	CRectangle * pR = dynamic_cast<CRectangle *>(pfig);
	CTriangle * pT = dynamic_cast<CTriangle *>(pfig);
	CCircle * pC =dynamic_cast<CCircle *>(pfig);
	CLine * pL = dynamic_cast <CLine *> (pfig);

	// then based on its type we select the figures with the same type and put them in the selected array

	if (pR) // if it is a rectangle put all the rectangles in the selected play array
	{
		for (int i=0;i<PlayCount;i++)
		{
			CRectangle * R = dynamic_cast<CRectangle *>(PlayList[i]);
			if (pfig != PlayList[i] && R)
				AddInSelected(PlayList[i]);
		}
	}
	else if (pT) // if it is a triangle put all the triangles in the selected play array
	{
		for (int i=0;i<PlayCount;i++)
		{
			CTriangle * T = dynamic_cast<CTriangle *>(PlayList[i]);
			if (pfig != PlayList[i] && T)
				AddInSelected(PlayList[i]);
		}
	}
	else if (pC) // if it is a Circl put all the Circles in the selected play array
	{
		for (int i=0;i<PlayCount;i++)
		{
			CCircle * C =dynamic_cast<CCircle *>(PlayList[i]);
			if (pfig != PlayList[i] && C)
				AddInSelected(PlayList[i]);
		}
	}
	else if (pL) // if it is a line put all the lines in the selected play array
	{
		for (int i=0;i<PlayCount;i++)
		{
			CLine * L = dynamic_cast <CLine *>(PlayList[i]);
			if (pfig != PlayList[i] && L)
				AddInSelected(PlayList[i]);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager:: SelectAllSameFillColor(CFigure * pfig)
{

	if (!pfig->IsFilled()) // if the given figure is not filled we put all the non filled figures in the selected play array
	{
		for (int i=0;i<PlayCount;i++)
			if (pfig != PlayList[i] && !PlayList[i]->IsFilled() )
				AddInSelected(PlayList[i]);
	}
	else // if it is filled 
	{
		color fill=pfig->getFillColor(); // we add all the figures with the same fill color in the selected play array
		for (int i=0;i<PlayCount;i++)
			if (pfig != PlayList[i] && PlayList[i]->getFillColor() == fill)
				AddInSelected(PlayList[i]);
	}
}

////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager:: SelectAllSameTypeAndFillColor(CFigure * pfig)
{
	// first we need to identify the type of the given figure
	CRectangle * pR = dynamic_cast<CRectangle *>(pfig);
	CTriangle * pT = dynamic_cast<CTriangle *>(pfig);
	CCircle * pC =dynamic_cast<CCircle *>(pfig);
	CLine * pL = dynamic_cast <CLine *> (pfig);
	if (pR)
	{
		for (int i=0;i<PlayCount;i++)
		{
			// here we loop on the array and if the 
			CRectangle * R = dynamic_cast<CRectangle *>(PlayList[i]);
			if (pfig != PlayList[i] && R)

				if (pfig->IsFilled() ==PlayList[i]->IsFilled()) //here we check if both of them is filled or both of them is unfilled
				{
					if (!pfig->IsFilled()) // if they both are non filled then they are with same type and same fillcolor
						AddInSelected(PlayList[i]);
					else if(pfig->getFillColor()==PlayList[i]->getFillColor()) //check if they have the same fill color or not
						AddInSelected(PlayList[i]);
				}
		}
	}
	else if (pT)
	{
		for (int i=0;i<PlayCount;i++)
		{
			CTriangle * T = dynamic_cast<CTriangle *>(PlayList[i]);
			if (pfig != PlayList[i] && T)
				if (pfig->IsFilled() ==PlayList[i]->IsFilled())
				{
					if (!pfig->IsFilled())
						AddInSelected(PlayList[i]);
					else if(pfig->getFillColor()==PlayList[i]->getFillColor())
						AddInSelected(PlayList[i]);
				}
		}
	}
	else if (pC)
	{
		for (int i=0;i<PlayCount;i++)
		{
			CCircle * C =dynamic_cast<CCircle *>(PlayList[i]);
			if (pfig != PlayList[i] && C)
				if (pfig->IsFilled() ==PlayList[i]->IsFilled())
				{
					if (!pfig->IsFilled())
						AddInSelected(PlayList[i]);
					else if(pfig->getFillColor()==PlayList[i]->getFillColor())
						AddInSelected(PlayList[i]);
				}
		}
	}
	else if (pL)
	{
		for (int i=0;i<PlayCount;i++)
		{
			CLine * L = dynamic_cast <CLine *>(PlayList[i]);
			if (pfig != PlayList[i] && L)
				if (pfig->IsFilled() ==PlayList[i]->IsFilled())
				{
					if (!pfig->IsFilled())
						AddInSelected(PlayList[i]);
					else if(pfig->getFillColor()==PlayList[i]->getFillColor())
						AddInSelected(PlayList[i]);
				}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::SelectAllSameLargestArea()
{
	// this function assumes that the array is sorted
	AddInSelected(PlayList[PlayCount-1]); // the last figure is the lagest figure
	int i = PlayCount-2; // we start looping from the pre last figure
	while (i>=0)
	{
		if (PlayList[i]->getArea()==PlayList[PlayCount-1]->getArea()) // if the figure is with the same area of the last figure the add it
			AddInSelected(PlayList[i]);
		else // if not so break as the previous figures are then smaller
			return;
	}
}

////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::SortPlayListWithArea()//sort the play list ascendingly
{
	for (int i=0;i<PlayCount;i++)
		for (int j=0;j<PlayCount-1;j++)
			if (PlayList[j]->getArea() >PlayList[j+1]->getArea())
				swap(PlayList[j],PlayList[j+1]);
}

////////////////////////////////////////////////////////////////////////////////////
bool ApplicationManager:: FoundInSelected(CFigure *pfig)
{
	// for play mode only !!
	for (int i=0;i<Selectedplaycount;i++)
		if (SelectedPlay[i]==pfig)
			return true;
	return false;
}

////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(Point P) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	///Add your code here to search for a figure given a point x,y	
	if (pOut->get_Mode()==MODE_DRAW)
	{
		for(int i = FigCount-1; i >= 0; i--)
		{
			if (FigList[i]->CheckPointFound(P))
				return FigList[i];
		}
	}
	else //play mode
		for (int i= PlayCount-1;i>=0;i--)
			if (PlayList[i]->CheckPointFound(P))
				return PlayList[i];


	return NULL;
}

///////////////////////////////////////////////////////////////////////////
void ApplicationManager::SaveAll(ofstream &OutFile)const
{
	/// first we save the ui information by using getters of the ouyput to get the colors information
	color drw=pOut->getCrntDrawColor();
	string drwclr =to_string(drw.ucRed)+"  "+to_string(drw.ucGreen)+"  "+to_string(drw.ucBlue)+"  ";
	OutFile<<drwclr;

	color fill = pOut->getCrntFillColor(); 
	string flclr=to_string(fill.ucRed)+"  "+to_string(fill.ucGreen)+"  "+to_string(fill.ucBlue)+"  ";
	OutFile<<flclr;

	color bg=pOut->getBackGroundColor();
	string bgclr=to_string(bg.ucRed)+"  "+to_string(bg.ucGreen)+"  "+to_string(bg.ucBlue);
	OutFile<<bgclr<<endl;

	/// every figure saves it self to the file
	OutFile<<FigCount<<endl;
	for (int i=0;i<FigCount;i++)
		FigList[i]->Save(OutFile); /// every figure saves it self to the file
}

void ApplicationManager::Load(ifstream &InFile)
{
	int x,y,z;
	InFile>>x>>y>>z;
	color drw(x,y,z);
	pOut->setCrntDrawColor(drw);

	InFile>>x>>y>>z;
	color fill(x,y,z);
	pOut->setCrntFillColor(fill);

	InFile>>x>>y>>z;
	color bk(x,y,z);
	pOut->setCrntBKGrndColor(bk);
}
////////////////////////////////////////////////////////////////////////////////////
CFigure** ApplicationManager::CopyAll() // For Sramble and find in the play mode ,, as this action works on its own arrays 
{

	CFigure** CopyFig = new CFigure* [FigCount];
	for(int i=0 ; i<FigCount;i++)
		CopyFig[i] = FigList[i]->Copy();
	return CopyFig;

}

////////////////////////////////////////////////////////////////////
void ApplicationManager:: CopyAllList()  /// For Pick and hide in the play mode
{
	for(int i = 0; i<FigCount; i++)
	{
		PlayList[i] = FigList[i]->Copy();
	}
	PlayCount = FigCount;
}
/////////////////////////////////////////////////////////////
void ApplicationManager::DeleteAllList()
{
	if (pOut->get_Mode()==MODE_DRAW)
	{
		for(int i = 0; i<FigCount; i++)
		{
			delete FigList[i];
			FigList[i] = NULL;
			///Selected[i]=NULL;
		}
		FigCount=0;
		SelectedCount=0;
		ClearClipboard();
	}
	else // play mode // delete the play list
	{
		for (int i=0;i<PlayCount;i++)
		{
			delete PlayList[i];
			PlayList[i]=NULL;
		}
		PlayCount=0;
	}
}
//////////////////////////////////////////////////////////
void ApplicationManager::Copy(){

	CFigure* pCopy;
	ClearClipboard();

	for(int i = 0; i<SelectedCount; i++){
		pCopy = Selected[i]->Copy();
		AddInClipboard(pCopy);
	}

}

////////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::Cut(){

	CFigure* pCut;
	ClearClipboard();

	for(int i = 0; i<SelectedCount; i++){

		pCut = Selected[i];

		ShiftFiglistDown(Selected[i]);

		Selected[i] = NULL;

		ShiftSelectedlistDown(i);
		i--;

		AddInClipboard(pCut);
		/*
		pCut = Selected[i]->Copy();

		ShiftFiglistDown(Selected[i]);

		delete Selected[i];
		Selected[i] = NULL;

		ShiftSelectedlistDown(i);
		i--;

		AddInClipboard(pCut); */

	}

}

///////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::Delete(){

	for(int i = 0; i<SelectedCount; i++){

		/*delete FigList[i]; //func delete in Cfig // 2 lines  !!!
		FigList[i] = NULL;*/

		ShiftFiglistDown(Selected[i]);

		delete Selected[i];
		Selected[i] = NULL;

		ShiftSelectedlistDown(i);

		i--;
	}

}
//////////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager :: Delete(CFigure * pfig)
{
	/////for play mode 
	/// it takes a specific figure and deletes it from the array
	for (int i=0;i<PlayCount;i++)
		if(PlayList[i]==pfig)
		{
			delete PlayList[i];
			PlayList[i]=NULL;
			ShiftFiglistDown(PlayList[i]);

			return;
		}
}

///////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::Paste(){

	Action* pAct = NULL;

	pAct = new MoveAction(this, Clipboard, ClipboardCount);
	bool Excuted=pAct->Execute();
	delete pAct;

	if (!Excuted)
		return;

	for(int i = 0; i<ClipboardCount; i++){

		CFigure* pFig = Clipboard[i]->Cut(); //with same ID

		pFig->SetSelected(true);
		AddFigure(pFig);
		AddInSelected(pFig);

	}

}
//////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::ShiftFiglistDown(CFigure* pFig){

	if (pOut->get_Mode()==MODE_DRAW)
	{
		int i = 0;
		while(FigList[i] != pFig) {i++;} //get the index of the removed figure

		for(; i < FigCount-1; i++){
			FigList[i] = FigList[i+1];
		}

		FigList[i] = NULL;
		FigCount--;
	}
	else /// play mode 
	{
		int i = 0;
		while(PlayList[i] != pFig) {i++;} //get the index of the removed figure

		for(; i < PlayCount-1; i++){
			PlayList[i] = PlayList[i+1];
		}

		PlayList[i] = NULL;
		PlayCount--;

	}
}

//////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::ShiftSelectedlistDown(int index){

	if (pOut->get_Mode()==MODE_DRAW)
	{
		for(; index<SelectedCount-1; index++){
			Selected[index] = Selected[index+1];
		}

		Selected[index] = NULL;
		SelectedCount--;
	}
	else
	{
		for(; index<Selectedplaycount-1; index++)
			SelectedPlay[index] = SelectedPlay[index+1];


		SelectedPlay[index] = NULL;
		Selectedplaycount--;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::ShiftFiglistUp(CFigure* pFig){

	int i = 0;
	while(FigList[i] != pFig) {i++;} //get the index of the removed figure

	for(; i>0; i--){

		FigList[i] = FigList[i-1];
	}

	FigList[0] = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::ShiftSelectedlistUp(int index){

	for(; index>0; index--){

		Selected[index] = Selected[index-1];
	}

	Selected[0] = NULL;
}

///////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::Rotate(int RotationalAngle){

	bool check = false;

	for(int i=0;i<SelectedCount;i++)
	{
		check = Selected[i]->CanRotate(RotationalAngle, pOut);
	}

	if(!check){
		pOut->PrintMessage("Rotation is invalid");
		return;
	}

	for(int i=0;i<SelectedCount;i++)
	{
		Selected[i]->Rotate(RotationalAngle);
	}
}

//////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::Resize(float Factor)
{
	for (int i=0;i<SelectedCount;i++)
	{
		if (! Selected[i]->CanResize(Factor,pOut)) // we check first that the figures won't get out of the window 
			// every figure checks itself 
		{
			pOut->PrintMessage("Resize is invalid");
			return;
		}
	}

	for (int i=0;i<SelectedCount;i++)
	{
		Selected[i]->Resize(Factor); // every figure resizes itself
	}

}

/////////////////////////////////////////////////////////////////////////////////////
//Put the fig at the bottom of the FigList
void ApplicationManager::BringFront(){

	CFigure* pFig;
	if (pOut->get_Mode()==MODE_DRAW)
	{
		int Tempcount = SelectedCount;
		for(int i = 0; i<Tempcount; i++) 
		{
			pFig = Selected[i]->Copy();
			pFig->SetSelected(true); //May the user want to make some other operation on it

			ShiftFiglistDown(Selected[i]);

			delete Selected[i];
			Selected[i] = NULL; 

			ShiftSelectedlistDown(i);

			i--;
			Tempcount--;

			AddFigure(pFig);
			AddInSelected(pFig);
		}
	}
	else // if we are in the play mode we will work on the playmode arrays
	{
		int Tempcount = Selectedplaycount ;
		for(int i = 0; i<Tempcount; i++) 
		{
			pFig = SelectedPlay[i]->Copy(); 
			ShiftFiglistDown(SelectedPlay[i]); // shift el play list

			delete SelectedPlay[i]; 
			SelectedPlay[i] = NULL; 

			ShiftSelectedlistDown(i);

			i--;
			Tempcount--;

			AddFigure(pFig);
			AddInSelected(pFig);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//Put the Fig at the Top of the FigList
void ApplicationManager::SendBack(){

	CFigure* pFig;

	for(int i = 0; i<SelectedCount; i++){ 

		pFig = Selected[i]->Copy();
		pFig->SetSelected(true); //may the user want to make some other operation

		ShiftFiglistUp(Selected[i]);

		delete Selected[i]; 
		Selected[i] = NULL;

		ShiftSelectedlistUp(i);

		//i++;

		FigList[0] = pFig; 
		Selected[0] = pFig;
	}
}

///////////////////////////////////////////////////////////////////////////////////////
bool ApplicationManager::ChangeBorderWidth(int width)
{
	bool change=false;

	for(int i=0;i<SelectedCount;i++)
	{
		Selected[i]->ChngBorderWidth(width);
		change = true;	
	}
	return change;
}

void ApplicationManager::Zooming(float zoom_width)
{
	for(int i=0; i< FigCount ; i++)
	{
		FigList[i]->ChngBorderWidth((int)(FigList[i]->getBorderWidth()*zoom_width));
	}
}
////////////////////////////////////////////////////////////////////////////////////
bool ApplicationManager::ChangeDrawClr(color DrawClr)
{
	bool change=false;
	for(int i = 0; i<SelectedCount; i++)
	{
		Selected[i]->ChngDrawClr(DrawClr);
		change=true;
	}
	return change;
}

/////////////////////////////////////////////////////////////////////////////////////
bool ApplicationManager::ChangeFillClr(color FillClr)
{
	bool change=false;
	for(int i=0; i<SelectedCount; i++)
	{
		Selected[i]->ChngFillClr(FillClr);
		change=true;
	}
	return change;
}
///////////////////////////////////////////////////////////////////////////////////////
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	pOut->ClearDrawArea();

	if (pOut->get_Mode()==MODE_DRAW){
		for(int i=0; i<FigCount; i++)
			FigList[i]->Draw(pOut);//Call Draw function (virtual member fn)

		if(pOut->getZoomMode()){

			if(pOut->get_zoom_factor() != 1){
				pOut->CreateZoomToolBar();
				pOut->ClearStatusBar();
			}
			else{
				pOut->CreateDrawToolBar();
				pOut->setZoomMode(false);
			}
		}
	}

	else{ // if play mode 
		for (int i=0; i< PlayCount;i++)
			PlayList[i]->Draw(pOut);
	}
}

//////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::UpdateInterface(CFigure** List, int Size) const{

	for (int i=0; i< Size;i++)
		List[i]->Draw(pOut);
}

/////////////////////////////////////////////////////////////////////////////////////
int ApplicationManager::getFigCount()const
{
	if (pOut->get_Mode()==MODE_DRAW)
		return FigCount;
	else
		return PlayCount;
}

///////////////////////////////////////////////////////////////////////////////
int ApplicationManager::getClipboardCount() const
{
	return ClipboardCount;
}
/////////////////////////////////////////////////////////////////////////////////////
int ApplicationManager::getSelectedCount()const
{
	if (pOut->get_Mode() ==MODE_DRAW)
		return SelectedCount;
	else
		return Selectedplaycount;
}
///////////////////////////////////////////////////////////////////////////////
void ApplicationManager::SetWastedClick(Point Click){
	wastedset=true;
	WastedClick=Click;
}

////////////////////////////////////////////////////////////////////////////////////
/*Point ApplicationManager:: defualtWasted()
{
Point p;
p.x=1300;
p.y=0;
return p;
///returns a click to an empty place in the toolbar ,, so no action is executed
}*/
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];

	for(int i=0; i<ClipboardCount; i++)
		delete Clipboard[i];

	delete pIn;
	delete pOut;

}
