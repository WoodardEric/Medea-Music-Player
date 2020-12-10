#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "portaudio.h"
#include <wx/wx.h>
#include <wx/dir.h>
#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "icons.xpm"
#endif
#include <wx/button.h>
#include <wx/slider.h>

#include "MainPanel.h"
#include "AudioManager.h"
#include "MusicFile.h"
#include "IDs.h"
#include "index.h"

#include<fstream>
#include <string>
#include <sstream>
#include <vector>

using std::fstream;
using std::vector;

class MainFrame : public wxFrame
{
public:
	MainFrame(wxSize size);
	virtual ~MainFrame();
	void setCurrTrack(Node *track);
	void OnExit(wxCommandEvent &event);
	void OnDir(wxCommandEvent &event);

	void OnScan(wxCommandEvent &event);
	void OnAbout(wxCommandEvent &event);
	
	void OnTitle(wxCommandEvent &event);
	void OnAlbum(wxCommandEvent &event);
	void OnArtist(wxCommandEvent &event);

	void OnPlay(wxCommandEvent &event);
	void OnPause(wxCommandEvent &event);
	void OnStop(wxCommandEvent &event);
	void OnNext(wxCommandEvent &event);
	void OnPrev(wxCommandEvent &event);
	
	void OnLoop(wxCommandEvent &event);
	void OnLoopList(wxCommandEvent &event);

	void OnSave(wxCommandEvent &event);
	void OnLoad(wxCommandEvent &event);

	void OnSlider(wxCommandEvent &event);
	void OnTimeSlider(wxCommandEvent &event);

	void OnTimer(wxTimerEvent &event);
	void OnTimeSliderRealse(wxMouseEvent &event);

	void OnKeyDown(wxKeyEvent &event);
	void saveCurrPlaylist(string path);
	void loadCurrPlayList (string path);
	//void OnLeftD( &event);

	//void readSample();
	void toggleLoopTrack() {trackLoop = !trackLoop;}
	bool isTrackLoop() {return trackLoop;}

	void toggleLoopList() { listLoop = !listLoop; }
	bool isListLoop() { return listLoop; }

	void readWavInfo(const string &path);
	void initMasterLibrary();
	void saveMasterList();
private:
	wxTimer *timer;

	wxMenu *fileMenu;
	wxMenu *libraryMenu;
	wxMenu *controlMenu;
	wxMenu *playListMenu;
	wxMenu *helpMenu;
	wxMenuBar *menuBar;

	MainPanel *mainPanel;
	wxPanel *parent;
	wxBoxSizer *hbox;
	
	wxStatusBar *statusBar;
	wxToolBar *toolBar;
	wxSlider *timeSlider; 
	wxSlider *volSlider;
	
	vector<Track> masterLibrary;
	vector<Track*> albumIndex;
	vector<Track*> artistIndex;
	
	Playlist *masterPlayList;
	
	MusicFile *file;
	AudioManager *audio;
	Node *currTrackPTR;

	bool listLoop;
	bool trackLoop;
	
	string mLibraryPath;
};


void advanceToNextTag(fstream &inFile);

#endif

