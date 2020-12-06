#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "portaudio.h"
#include <wx/wx.h>
#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "icons.xpm"
#endif
#include <wx/button.h>
#include <wx/slider.h>

#include "PlaylistPanel.h"
#include "MiddlePanel.h"
#include "AudioManager.h"
#include "MusicFile.h"

#include<fstream>

using std::fstream;

// IDs for the controls and the menu commands
enum
{
	// Menu event IDs
	wxID_PLAY = 1,
	wxID_PAUSE,
	wxID_NEXT,
	wxID_PREV,
	wxID_LOOP,
	wxID_LOOPALL,

	ID_SLIDER,
    //    wxID_STOP,   [built-in to wxWidgets]
    //    wxID_ABOUT,  [built-in to wxWidgets]
    //    wxID_EXIT,   [built-in to wxWidgets]
        // Control event IDs
	wxID_TIMER,
	ID_ABOUT
};

class MainFrame : public wxFrame
{
public:
	MainFrame(wxSize size);
	virtual ~MainFrame();
	void OnExit(wxCommandEvent &event);
	void OnAbout(wxCommandEvent &event);

	void OnPlay(wxCommandEvent &event);
	void OnPause(wxCommandEvent &event);
	void OnStop(wxCommandEvent &event);
	void OnNext(wxCommandEvent &event);
	void OnPrev(wxCommandEvent &event);
	
	void OnLoop(wxCommandEvent &event);
	void OnLoopList(wxCommandEvent &event);

	void OnSlider(wxCommandEvent &event);

	void OnTimer(wxTimerEvent &event);
	void readSample();
private:
	wxTimer *timer;

	wxMenu *fileMenu;
	wxMenu *controlMenu;
	wxMenu *helpMenu;
	wxMenuBar *menuBar;

	wxPanel *mainPanel;
	wxBoxSizer *hbox;
	
	MiddlePanel *middlePanel;
	PlaylistPanel *rightPanel;
	wxToolBar *toolBar;

	wxSlider *volSlider;
	MusicFile file;
	AudioManager *audio;
	
};

#endif

