#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "portaudio.h"
#include <wx/wx.h>
#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "icons.xpm"
#endif
#include <wx/button.h>
#include <wx/slider.h>

#include "MainPanel.h"
#include "AudioManager.h"
#include "MusicFile.h"

#include<fstream>
#include <string>
#include <sstream>
#include <vector>

using std::fstream;
using std::vector;


// IDs for the controls and the menu commands
enum
{
	// Menu event IDs
	ID_PLAY = 1,
	ID_PAUSE,
	ID_NEXT,
	ID_PREV,
	ID_LOOP,
	ID_LOOPALL,
	ID_STOP,
	ID_SAVE,
	ID_LOAD,
	
    //    wxID_STOP,   [built-in to wxWidgets]
    //    wxID_ABOUT,  [built-in to wxWidgets]
    //    wxID_EXIT,   [built-in to wxWidgets]
        // Control event IDs
	// wxID_TIMER,
	ID_VOL_SLIDER,
	ID_TIME_SLIDER,

	ID_SELECT
};

class MainFrame : public wxFrame
{
public:
	MainFrame(wxSize size);
	virtual ~MainFrame();
	void setCurrTrack(Node *track);
	void OnExit(wxCommandEvent &event);
	void OnAbout(wxCommandEvent &event);

	void OnPlay(wxCommandEvent &event);
	void OnPause(wxCommandEvent &event);
	void OnStop(wxCommandEvent &event);
	void OnNext(wxCommandEvent &event);
	void OnPrev(wxCommandEvent &event);
	
	void OnLoop(wxCommandEvent &event);
	void OnLoopList(wxCommandEvent &event);

	void OnSave(wxCommandEvent &event);

	void OnSlider(wxCommandEvent &event);
	void OnTimeSlider(wxCommandEvent &event);

	void OnTimer(wxTimerEvent &event);
	void OnTimeSliderRealse(wxMouseEvent &event);

	void OnKeyDown(wxKeyEvent &event);
	void saveCurrPlaylist(string path);
	//void OnLeftD( &event);

	//void readSample();
	void toggleLoopTrack() {trackLoop = !trackLoop;}
	bool isTrackLoop() {return trackLoop;}

	void toggleLoopList() { listLoop = !listLoop; }
	bool isListLoop() { return listLoop; }

	void readWavInfo(const string &path);

private:
	wxTimer *timer;

	wxMenu *fileMenu;
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
	
	vector<Track> masterList;
	Playlist *masterPlayList;
	
	MusicFile *file;
	AudioManager *audio;
	Node *currTrackPTR;

	bool listLoop;
	bool trackLoop;

	
	
};


void advanceToNextTag(fstream &inFile);

#endif

