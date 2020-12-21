/**********************************************************************
 Medea: A Digital Music Player

 @file  MainFrame.h

 @brief:

 Manages the file menus, toolbar, statusbar, child panels,
 and communicates with audio and file managers.

 @author Eric Woodard
 @date   12/11/2020

 //TODO fix prev and next on looping
 **********************************************************************/
#ifndef MAINFRAME_H
#define MAINFRAME_H

 //ignores compile error about std function deprecation in wxWidgets' wxcrt.h
#pragma warning(disable : 4996)
#include "AudioManager.h"
#include "IDs.h"
#include "index.h"
#include "LibraryPanel.h"
#include "AudioFile.h"
#include "PlaylistPanel.h"

#include "AudioThread.h"

#include "portaudio.h"
#include <wx/wx.h>
#include <wx/button.h>
#include <wx/dir.h>
#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "icons.xpm"
#endif
#include <wx/slider.h>

#include<fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::vector;

enum class PaState
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
	Node *getCurrTrack() const { return currTrackPTR; }

	void OnDir(wxCommandEvent &event);
	void OnScan(wxCommandEvent &event);
	void OnExit(wxCommandEvent &event);
	
	void OnTitle(wxCommandEvent &event);
	void OnAlbum(wxCommandEvent &event);
	void OnArtist(wxCommandEvent &event);

	void OnPlay(wxCommandEvent &event);
	void OnNext(wxCommandEvent &event);
	void OnPrev(wxCommandEvent &event);
	
	void OnLoop(wxCommandEvent &event);
	void OnLoopList(wxCommandEvent &event);

	void OnSave(wxCommandEvent &event);
	void OnLoad(wxCommandEvent &event);
	void OnClear(wxCommandEvent &event);

	void OnAbout(wxCommandEvent &event);

	void OnSlider(wxCommandEvent &event);
	void OnTimeSlider(wxScrollEvent &event);
	//void OnTimeSliderScroll(wxScrollEvent &event);
	void OnTimeSliderFinish(wxScrollEvent &event);
	void OnTimer(wxTimerEvent &event);

	void loadCurrPlayList (string path);
	
	void toggleisPlaying();
	void toggleLoopTrack() {loopTrack = !loopTrack;}
	bool isTrackLoop() {return loopTrack;}

	void toggleLoopList() { loopAll = !loopAll; }
	bool isListLoop() { return loopAll; }

	bool getisPlaying() { return misPlaying; }
	void readWavInfo(const string &path);
	void saveMasterList();

	PlaylistPanel* getPlaylistPanel() { return mPlaylistPanel; }
	void setThread(string path);

private:
	wxTimer *timer;

	wxMenu *fileMenu;
	wxMenu *libraryMenu;
	wxMenu *controlMenu;
	wxMenu *playListMenu;
	wxMenu *helpMenu;
	wxMenuBar *menuBar;

	LibraryPanel *mLibraryPanel;
	PlaylistPanel *mPlaylistPanel;
	wxPanel *mParent;
	wxBoxSizer *hbox;
	
	wxStatusBar *statusBar;
	wxToolBar *toolBar;
	wxSlider *timeSlider; 
	wxSlider *volSlider;
	
	vector<Track> *mLibrary;
	vector<Track*> *mAlbumIndex;
	vector<Track*> *mArtistIndex;
	
	Node *currTrackPTR;

	bool loopAll;
	bool loopTrack;
	bool misPlaying;
	string mLibraryPath;

	AudioThread *mThread;
};

void advanceToNextTag(fstream &inFile);

#endif

