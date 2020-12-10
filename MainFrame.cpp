#include "MainFrame.h"

MainFrame::MainFrame(wxSize size)
	:wxFrame(NULL, wxID_ANY, "Medea Music Player", wxDefaultPosition, size)
{
	
	masterPlayList = new Playlist();
	readWavInfo("Data/altan.wav");
	readWavInfo("Data/07 September.wav");
	readWavInfo("Data/03 Minjor.wav");
	readWavInfo("Data/01 One More Time.wav");

	for (int i = 0; i <  masterList.size(); ++i)
	{
		masterPlayList->addFront(&masterList[i]);
	}

	//sets icon in top corner
	currTrackPTR = masterPlayList->front();
	file = new MusicFile(currTrackPTR->track->path);
	audio = new AudioManager(file);

	SetIcon(wxICON(icon));

	//setup menu bar
	fileMenu = new wxMenu;
	controlMenu = new wxMenu;
	playListMenu = new wxMenu;
	helpMenu = new wxMenu;
	

	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Exit Program");

	controlMenu->Append(ID_PLAY, "&Play\tCtrl-P", "Play or pause track");
	controlMenu->Append(ID_STOP, "&Stop\tCtrl-T", "Stop current track");
	controlMenu->Append(ID_NEXT, "&Next\tCtrl-N", "Skip to next track");
	controlMenu->Append(ID_PREV, "&Previous\tCtrl-B", "Skip to previous track");
	controlMenu->AppendSeparator();
	controlMenu->Append(ID_LOOP, "&Loop\tCtrl-L", "Loop current track");
	controlMenu->Append(ID_LOOPALL, "Loop &All\tCtrl-K", "Loop current playlist");

	playListMenu->Append(ID_SAVE, "&Save\tCtrl-S", "Save current playlist");
	playListMenu->Append(ID_LOAD, "Loa&d\tCtrl-D", "Load a playlist");

	helpMenu->Append(wxID_ABOUT, "&About\tCtrl-A", "About dialogue");
	menuBar = new wxMenuBar();

	menuBar->Append(fileMenu, "&File");
	menuBar->Append(controlMenu, "&Controls");
	menuBar->Append(playListMenu, "&Playlist");
	menuBar->Append(helpMenu, "&Help");
	SetMenuBar(menuBar);

	Bind(wxEVT_MENU, &MainFrame::OnExit, this,
	wxID_EXIT);
	Bind(wxEVT_MENU, &MainFrame::OnAbout, this,
	wxID_ABOUT);
	Bind(wxEVT_MENU, &MainFrame::OnNext, this,
	ID_NEXT);
	Bind(wxEVT_MENU, &MainFrame::OnPrev, this,
	ID_PREV);
	Bind(wxEVT_MENU, &MainFrame::OnLoopList, this,
	ID_LOOPALL);
	Bind(wxEVT_MENU, &MainFrame::OnSave, this,
		ID_SAVE);


	//set up wondow panels
	parent = new wxPanel(this);
	
	mainPanel = new MainPanel(parent, &masterPlayList);
	//mainPanel->setPlaylist(&masterPlayList);
	hbox = new wxBoxSizer(wxHORIZONTAL);
	hbox->Add(mainPanel, 1, wxEXPAND | wxALL, 5);
	parent->SetSizer(hbox);


	statusBar = new wxStatusBar(this, wxID_ANY);
	SetStatusBar(statusBar);
	statusBar->SetFieldsCount(3);
	statusBar->SetStatusText(wxT("Ready"), 0);


	toolBar = new wxToolBar(this, wxID_ANY,
	wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxNO_BORDER | wxTB_BOTTOM);
	wxInitAllImageHandlers();
	volSlider = new wxSlider(toolBar, ID_VOL_SLIDER, 100, 0, 100,
	wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);


	toolBar->AddControl(volSlider);
	wxBitmap bmpPlay(wxT("Resources/play.png"), wxBITMAP_TYPE_PNG);
	if (!bmpPlay.Ok()) { wxMessageBox(wxT("Sorry, could not load file.")); }
	wxBitmap bmpPrev(wxT("Resources/prev.png"), wxBITMAP_TYPE_PNG);
	if (!bmpPlay.Ok()) { wxMessageBox(wxT("Sorry, could not load file.")); }
	wxBitmap bmpNext(wxT("Resources/next.png"), wxBITMAP_TYPE_PNG);
	if (!bmpPlay.Ok()) { wxMessageBox(wxT("Sorry, could not load file.")); }

	toolBar->AddTool(ID_PREV, wxT("prev"), bmpPrev, "play previous");
	toolBar->AddTool(ID_PLAY, wxT("Play"), bmpPlay, "start/stop track");
	toolBar->AddTool(ID_NEXT, wxT("next"), bmpNext, "play next");

	timeSlider = new wxSlider(toolBar, ID_TIME_SLIDER, 0, 0, file->getDataSize(),
	wxDefaultPosition, wxSize(200, -1), wxSL_HORIZONTAL);
	timeSlider->SetTickFreq(audio->getFramesPerBuffer());
	toolBar->AddControl(timeSlider);
	toolBar->Realize();
	SetToolBar(toolBar);

	Bind(wxEVT_COMMAND_SLIDER_UPDATED, &MainFrame::OnSlider, this, ID_VOL_SLIDER);
	Bind(wxEVT_COMMAND_SLIDER_UPDATED, &MainFrame::OnTimeSlider, this, ID_TIME_SLIDER);
	
	Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::OnPlay, this,
	ID_PLAY);
	Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::OnNext, this,
	ID_NEXT);
	Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::OnPrev, this,
	ID_PREV);
	//Bind(wxKeyEvent, &MainFrame::OnChar, this, ID_SELECT);
	
	//mainPanel->Bind(wxEVT_CHAR_HOOK, &MainFrame::OnKeyDown, this);
	//mainPanel->Bind(wxEVT_LEFT_DCLICK, &MainFrame::OnLeftD, this);
	audio->openStream();
	timer = new wxTimer(this, 1);
	Bind(wxEVT_TIMER, &MainFrame::OnTimer, this);

	timer->Start(1);
}

MainFrame::~MainFrame()
{
	timer->Stop();
}

void MainFrame::setCurrTrack(Node *track)
{
	if (isTrackLoop())
	{
		file->seek(0);
	}
	if (track != nullptr)
	{
		audio->stopStream();
		currTrackPTR = track;
		delete file;
		file = new MusicFile(currTrackPTR->track->path);
		audio->resetCounter();
		audio->openStream();
		audio->startStream();
		statusBar->SetStatusText(currTrackPTR->track->title, 1);
		timeSlider->SetRange(0, file->getDataSize());
	}
	else
	{
		audio->stopStream();
	}
	
}

void MainFrame::OnTimer(wxTimerEvent &WXUNUSED(event))
{
	//checks the audio stream for errors and handles it by shuting it down
	//-9983 = stream is stopped
	if (audio->err < 0 && audio->err != -9983)
	{
		timer->Stop();
		wxMessageBox(audio->getErrorMessage());
		audio->Terminate();
		Close(true);
	}

	if (audio->isStreaming() && audio->getCounter() * 4 < file->getDataSize() + 1)
	{
		
		if (audio->getCounter() * 4 < file->getDataSize() - (audio->getFramesPerBuffer() * 2))
		{
			file->readSample(audio->buffer, audio->getBufferSize());
		}
		for (int i = 0; i < audio->getBufferSize(); ++i)
		{
			audio->buffer[i] *= audio->getVolume();
		}
		

		audio->err = Pa_WriteStream(audio->audioStream, audio->buffer, audio->getFramesPerBuffer());
		audio->increaseCounter();
		
		int n = file->getCurrTrackTime(audio->getCounter());
		int min = n / 60;
		n = n % 60;
		int sec = n;
		std::ostringstream stream;
		std::string trackTime;
		stream << min << ':' << sec;
		timeSlider->SetValue(audio->getCounter() * 4);
		statusBar->SetStatusText(stream.str(), 2);
	}
	else if (audio->getCounter() * 4 >= file->getDataSize())
	{
		setCurrTrack(currTrackPTR->next);
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
	if(currTrackPTR->next != nullptr)
	{
		setCurrTrack(currTrackPTR->next);
	}
	else
	{
		if (isListLoop())
		{
			setCurrTrack(masterPlayList->front());
		}
	}
}

void MainFrame::OnPrev(wxCommandEvent &WXUNUSED(event))
{
	if (currTrackPTR->prev != nullptr)
	{
		setCurrTrack(currTrackPTR->prev);
	}
	else
	{
		if (isListLoop())
		{
			setCurrTrack(masterPlayList->rear());
		}
	}
}

void MainFrame::OnLoop(wxCommandEvent &WXUNUSED(event))
{
	toggleLoopTrack();
}

void MainFrame::OnLoopList(wxCommandEvent &WXUNUSED(event))
{
	toggleLoopList();
}
void MainFrame::OnSave(wxCommandEvent &WXUNUSED(event))
{
	saveCurrPlaylist("Data/");
}
void MainFrame::OnSlider(wxCommandEvent &WXUNUSED(event))
{
	audio->setVolume(volSlider->GetValue() / 100.0f);
}

void MainFrame::OnTimeSlider(wxCommandEvent &WXUNUSED(event))
{
	audio->stopStream();
	audio->setCounter(timeSlider->GetValue() / 4);
	file->seek(timeSlider->GetValue());
	audio->clearBuffer();
	audio->startStream();
}

void MainFrame::OnTimeSliderRealse(wxMouseEvent &event)
{
	audio->clearBuffer();
	timer->Start();
}

void MainFrame::saveCurrPlaylist(string path)
{
	Node *ptr = mainPanel->getFront();
	fstream outFile(path + mainPanel->getListName(), ios_base::out);
	if (!outFile)
	{
		wxMessageBox(wxT("Could not load file." + mainPanel->getListName()));
		return;
	}

	while (ptr->next != nullptr)
	{
		outFile << ptr->track->title << ',' << ptr->track->path << '\n';
		ptr = ptr->next;
	}
	
	outFile << ptr->track->title << ',' << ptr->track->path;
}

void MainFrame::readWavInfo(const string &path)
{
	Track track;
	track.path = path;
	fstream inFile(path, ios::in | ios::binary);
	AudioHeader header(inFile);
	track.length = header.subChunk2Size / (header.sampleRate * header.numChannels * header.bitsPerSample / 8);
	inFile.seekg(header.subChunk2Size, ios_base::cur);

	char ID[4];
	uint32_t chunkSize;
	const char ListID[]{ 'L', 'I', 'S', 'T' };
	inFile.read(reinterpret_cast<char *>(&ID), sizeof(uint8_t) * 4);

	while (strncmp(ID, ListID, 4) != 0)
	{
		int junk;
		inFile.read(reinterpret_cast<char *>(&chunkSize), sizeof(uint32_t));
		inFile.read(reinterpret_cast<char *>(&junk), sizeof(uint8_t) * chunkSize);
		inFile.read(reinterpret_cast<char *>(&ID), sizeof(uint8_t) * 4);
	}
	const char INAM[]{ 'I', 'N', 'A', 'M' };
	const char IPRD[]{ 'I', 'P', 'R', 'D' };
	const char IART[]{ 'I', 'A', 'R', 'T' };
	const char ICRD[]{ 'I', 'C', 'R', 'D' };
	const char IGNR[]{ 'I', 'G', 'N', 'R' };
	const char ITRK[]{ 'I', 'T', 'R', 'K' };

	inFile.seekg(sizeof(uint8_t) * 4, ios_base::cur);
	inFile.read(reinterpret_cast<char *>(&ID), sizeof(uint8_t) * 4);


	while (!inFile.eof() || strncmp(ID, ITRK, 4) == 0)
	{
		inFile.read(reinterpret_cast<char *>(&ID), sizeof(uint8_t) * 4);
		inFile.seekg(sizeof(uint8_t) * 4, ios_base::cur);

		if (strncmp(ID, INAM, 4) == 0)
		{
			getline(inFile, track.title, '\0');
		}
		else if (strncmp(ID, IPRD, 4) == 0)
		{
			getline(inFile, track.album, '\0');
		}
		else if (strncmp(ID, IART, 4) == 0)
		{
			getline(inFile, track.artist, '\0');
		}
		else if (strncmp(ID, ICRD, 4) == 0)
		{
			inFile >> track.year;
		}
		else if (strncmp(ID, IGNR, 4) == 0)
		{
			getline(inFile, track.genre, '\0');
		}
		else if (strncmp(ID, ITRK, 4) == 0)
		{
			inFile >> track.trackNumber;
		}
		else
		{
			int size;
			inFile.read(reinterpret_cast<char *>(&size), sizeof(uint8_t) * 4);
			inFile.seekg(size, ios_base::cur);
		}
		advanceToNextTag(inFile);
	}

	inFile.close();
	masterList.push_back(track);
}

void advanceToNextTag(fstream &inFile)
{
	char delem;
	while (inFile.peek() == '\0')
	{
		inFile.get(delem);
	}
}