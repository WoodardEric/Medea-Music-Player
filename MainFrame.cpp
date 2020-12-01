#include "MainFrame.h"

MainFrame::MainFrame(wxSize size)
	:wxFrame(NULL, wxID_ANY, "Medea Music Player", wxDefaultPosition, size)
{
	SetIcon(wxICON(icon));

	wxMenu *fileMenu = new wxMenu;
	wxMenu *controlMenu = new wxMenu;
	wxMenu *helpMenu = new wxMenu;
	
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Exit Program");

	controlMenu->Append(wxID_PLAY, "&Play\tCtrl-P", "Play or pause track");
	controlMenu->Append(wxID_STOP, "&Stop\tCtrl-S", "Stop current track");
	controlMenu->Append(wxID_NEXT, "&Next\tCtrl-N", "Skip to next track");
	controlMenu->Append(wxID_STOP, "&Previous\tCtrl-B", "Skip to previous track");
	controlMenu->AppendSeparator();
	controlMenu->Append(wxID_LOOP, "&Loop\tCtrl-L", "Loop current track");
	controlMenu->Append(wxID_LOOPALL, "Loop &All\tCtrl-K", "Loop current playlist");

	wxMenuBar *menuBar = new wxMenuBar();

	menuBar->Append(fileMenu, "&File");
	menuBar->Append(controlMenu, "&Controls");
	SetMenuBar(menuBar);

	Bind(wxEVT_MENU, &MainFrame::OnExit, this,
		wxID_EXIT);
	Bind(wxEVT_MENU, &MainFrame::OnAbout, this,
		wxID_ABOUT);

	wxPanel *mainPanel = new wxPanel(this, wxID_ANY);
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

	//wxPanel *rightPanel = new wxPanel(mainPanel);
	MiddlePanel *middlePanel = new MiddlePanel(mainPanel);
	hbox->Add(middlePanel, 1, wxEXPAND | wxALL, 5);
	PlaylistPanel *rightPanel = new PlaylistPanel(mainPanel);
	hbox->Add(rightPanel, 1, wxEXPAND | wxALL, 5);

	mainPanel->SetSizer(hbox);

}

void MainFrame::OnExit(wxCommandEvent &WXUNUSED(event))
{
	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent &WXUNUSED(event))
{
	
}

void MainFrame::OnPlay(wxCommandEvent &WXUNUSED(event))
{
}

void MainFrame::OnPause(wxCommandEvent &WXUNUSED(event))
{
}

void MainFrame::OnStop(wxCommandEvent &WXUNUSED(event))
{
}

void MainFrame::OnNext(wxCommandEvent &WXUNUSED(event))
{
}

void MainFrame::OnPrev(wxCommandEvent &WXUNUSED(event))
{
}

void MainFrame::OnLoop(wxCommandEvent &WXUNUSED(event))
{
}

void MainFrame::OnLoopList(wxCommandEvent &WXUNUSED(event))
{
}
