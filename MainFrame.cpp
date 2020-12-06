#include "MainFrame.h"

MainFrame::MainFrame(wxSize size)
	:wxFrame(NULL, wxID_ANY, "Medea Music Player", wxDefaultPosition, size), 
	 file("Data/altan.wav")
{
	//sets icon in top corner
	SetIcon(wxICON(icon));

	//setup menu bar
	fileMenu = new wxMenu;
	controlMenu = new wxMenu;
	helpMenu = new wxMenu;
	
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Exit Program");

	controlMenu->Append(wxID_PLAY, "&Play\tCtrl-P", "Play or pause track");
	controlMenu->Append(wxID_STOP, "&Stop\tCtrl-S", "Stop current track");
	controlMenu->Append(wxID_NEXT, "&Next\tCtrl-N", "Skip to next track");
	controlMenu->Append(wxID_STOP, "&Previous\tCtrl-B", "Skip to previous track");
	controlMenu->AppendSeparator();
	controlMenu->Append(wxID_LOOP, "&Loop\tCtrl-L", "Loop current track");
	controlMenu->Append(wxID_LOOPALL, "Loop &All\tCtrl-K", "Loop current playlist");

	helpMenu->Append(ID_ABOUT, "&About\tCtrl-A", "About dialogue");
	menuBar = new wxMenuBar();

	menuBar->Append(fileMenu, "&File");
	menuBar->Append(controlMenu, "&Controls");
	menuBar->Append(helpMenu, "&Help");
	SetMenuBar(menuBar);

	Bind(wxEVT_MENU, &MainFrame::OnExit, this,
		wxID_EXIT);
	Bind(wxEVT_MENU, &MainFrame::OnAbout, this,
		ID_ABOUT);

	//set up wondow panels
	mainPanel = new wxPanel(this, wxID_ANY);
	hbox = new wxBoxSizer(wxHORIZONTAL);
	
	//wxPanel *rightPanel = new wxPanel(mainPanel);
	middlePanel = new MiddlePanel(mainPanel);
	hbox->Add(middlePanel, 1, wxEXPAND | wxALL, 5);
	rightPanel = new PlaylistPanel(mainPanel);
	hbox->Add(rightPanel, 1, wxEXPAND | wxALL, 5);
	mainPanel->SetSizer(hbox);

	toolBar = new wxToolBar(this, wxID_ANY,
		wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxNO_BORDER | wxTB_BOTTOM);
	wxInitAllImageHandlers();

	volSlider = new wxSlider(toolBar, ID_SLIDER, 100, 0, 100,
		wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);
	toolBar->AddControl(volSlider);
	wxBitmap bmpPlay(wxT("Resources/play.png"), wxBITMAP_TYPE_PNG);
	if (!bmpPlay.Ok()) { wxMessageBox(wxT("Sorry, could not load file.")); }
	
	toolBar->AddTool(wxID_PLAY, wxT("Play"), bmpPlay);
	toolBar->Realize(); 
	SetToolBar(toolBar);
	
	Bind(wxEVT_COMMAND_SLIDER_UPDATED, &MainFrame::OnSlider, this, ID_SLIDER);
	Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::OnPlay, this,
		wxID_PLAY);
	
	audio = new AudioManager(&file);
	audio->openStream();
	timer = new wxTimer(this, 1);
	Bind(wxEVT_TIMER, &MainFrame::OnTimer, this);
	timer->Start(1);
}

MainFrame::~MainFrame()
{
	timer->Stop();
}

void MainFrame::OnTimer(wxTimerEvent &WXUNUSED(event))
{
	if (audio->isStreaming())
	{
		
		file.readSample(audio->buffer, audio->getBufferSize());
		for (int i = 0; i < audio->getBufferSize(); ++i)
		{
			audio->buffer[i] *= audio->getVolume();
		}

		audio->err = Pa_WriteStream(audio->audioStream, audio->buffer, audio->getFramesPerBuffer());
	
	}
}

void MainFrame::OnExit(wxCommandEvent &WXUNUSED(event))
{
	timer->Stop();
	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent &WXUNUSED(event))
{
	wxString message("Medea Music Player: \nBy Eric Woodard for cs151\n A simple audio player");
	wxMessageBox(message);
}

void MainFrame::OnPlay(wxCommandEvent &WXUNUSED(event))
{
	if (!audio->isStreaming())
	{
		audio->startStream();
	}
	else
	{
		audio->stopStream();
	}
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

void MainFrame::OnSlider(wxCommandEvent &event)
{
	audio->setVolume(volSlider->GetValue() / 100.0f);
}
