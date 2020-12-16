#ifndef MAINFRAME_H
#define MAINFRAME_H

#pragma warning(disable : 4996)
#include "AudioManager.h"
#include "IDs.h"
#include "index.h"
#include "MainPanel.h"
#include "MusicFile.h"

#include "portaudio.h"
#include <wx/wx.h>
#include <wx/dir.h>
#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "icons.xpm"
#endif
#include <wx/button.h>
#include <wx/slider.h>

#include<fstream>
#include <string>
#include <vector>

using std::fstream;
using std::vector;

enum PaState
{
	ACTIVE = 0,
	STOPPED = 1,
};
class MainFrame : public wxFrame
{
public:
	MainFrame(wxSize size, 
		 vector<Track> &masterVec, 
		 vector<Track*> &albumIndex, 
		 vector<Track*> &artistIndex);
	virtual ~MainFrame();

	void initMenu();
	void initToolBar();

	void setCurrTrack(Node *track);
	
	void OnDir(wxCommandEvent &event);
	void OnScan(wxCommandEvent &event);
	void OnExit(wxCommandEvent &event);
	
	void OnTitle(wxCommandEvent &event);
	void OnAlbum(wxCommandEvent &event);
	void OnArtist(wxCommandEvent &event);

	void OnPlay(wxCommandEvent &event);
	void OnPause(wxCommandEvent &event);
	void OnNext(wxCommandEvent &event);
	void OnPrev(wxCommandEvent &event);
	
	void OnLoop(wxCommandEvent &event);
	void OnLoopList(wxCommandEvent &event);

	void OnSave(wxCommandEvent &event);
	void OnLoad(wxCommandEvent &event);
	void OnClear(wxCommandEvent &event);

	void OnAbout(wxCommandEvent &event);

	void OnSlider(wxCommandEvent &event);
	void OnTimeSlider(wxCommandEvent &event);

	void OnTimer(wxTimerEvent &event);

	void loadCurrPlayList (string path);
	
	void toggleLoopTrack() {trackLoop = !trackLoop;}
	bool isTrackLoop() {return trackLoop;}

	void toggleLoopList() { listLoop = !listLoop; }
	bool isListLoop() { return listLoop; }

	bool getisPlaying() { return misPlaying; }
	void readWavInfo(const string &path);
	void saveMasterList();

private:
	wxTimer *timer;

	wxMenu *fileMenu;
	wxMenu *libraryMenu;
	wxMenu *controlMenu;
	wxMenu *playListMenu;
	wxMenu *helpMenu;
	wxMenuBar *menuBar;

	MainPanel *mPanel;
	wxPanel *mParent;
	wxBoxSizer *hbox;
	
	wxStatusBar *statusBar;
	wxToolBar *toolBar;
	wxSlider *timeSlider; 
	wxSlider *volSlider;
	
	vector<Track> *mLibrary;
	vector<Track*> *mAlbumIndex;
	vector<Track*> *mArtistIndex;
	
	
	MusicFile *mFile;
	AudioManager *audio;
	Node *currTrackPTR;

	bool listLoop;
	bool trackLoop;
	bool misPlaying;
	string mLibraryPath;
};

void advanceToNextTag(fstream &inFile);

#endif

