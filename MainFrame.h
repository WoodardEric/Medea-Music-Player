#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "icons.xpm"
#endif
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

    //    wxID_STOP,   [built-in to wxWidgets]
    //    wxID_ABOUT,  [built-in to wxWidgets]
    //    wxID_EXIT,   [built-in to wxWidgets]
        // Control event IDs
};

class MainFrame : public wxFrame
{
public:
	MainFrame(wxSize size);

	void OnExit(wxCommandEvent &event);
	void OnAbout(wxCommandEvent &event);

	void OnPlay(wxCommandEvent &event);
	void OnPause(wxCommandEvent &event);
	void OnStop(wxCommandEvent &event);
	void OnNext(wxCommandEvent &event);
	void OnPrev(wxCommandEvent &event);

	void OnLoop(wxCommandEvent &event);
	void OnLoopList(wxCommandEvent &event);
};

#endif

