#include "MainFrame.h"
//TODO handle no selected track and finish orginizing MAINFRAME, Add loop 
MainFrame::MainFrame(wxSize size,
	 vector<Track> &masterVec,
	 vector<Track *> &albumIndex,
	 vector<Track *> &artistIndex)
	:wxFrame(NULL, wxID_ANY, "Medea Music Player", wxDefaultPosition, size)
{
	mLibrary = &masterVec;
	mAlbumIndex = &albumIndex;
	mArtistIndex = &artistIndex;
	mLibraryPath = "Data/"; 
	masterPlayList = new Playlist();
	misPlaying = false;

	mFile = nullptr;
	audio = new AudioManager();

	//sets icon in top corner
	SetIcon(wxICON(icon));
	
	initMenu();
	
	mParent = new wxPanel(this);
	mPanel = new MainPanel(mParent, &masterPlayList, mLibrary, *mAlbumIndex, *mArtistIndex);
	
	hbox = new wxBoxSizer(wxHORIZONTAL);
	hbox->Add(mPanel, 1, wxEXPAND | wxALL, 5);
	mParent->SetSizer(hbox);

	initToolBar();

	statusBar = new wxStatusBar(this, wxID_ANY);
	SetStatusBar(statusBar);
	statusBar->SetFieldsCount(3);
	statusBar->SetStatusText(wxT("Ready"), 0);

	//audio->openStream();

	timer = new wxTimer(this, 1);
	Bind(wxEVT_TIMER, &MainFrame::OnTimer, this);
	timer->Start(1);
}

/*It is important to stop the timer otherwise wxWidgets throws an exception*/
MainFrame::~MainFrame()
{
	timer->Stop();
	delete mFile;
	delete audio;
}

/*initializes menu items and events*/
void MainFrame::initMenu()
{
	fileMenu = new wxMenu;
	libraryMenu = new wxMenu;
	controlMenu = new wxMenu;
	playListMenu = new wxMenu;
	helpMenu = new wxMenu;

	fileMenu->Append(ID_DIR, "Set &Libarary Path", "Select directory to music library");
	fileMenu->Append(ID_SCAN, "&Scan Library", "Scan music library for files");
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Exit Program");

	libraryMenu->Append(ID_TITLE, "Sort by &Title", "Sort Library by song title");
	libraryMenu->Append(ID_ALBUM, "Sort by &Album", "Sort Library by song album");
	libraryMenu->Append(ID_ARTIST, "Sort by A&rtist", "Sort Library by song artist");

	controlMenu->Append(ID_PLAY, "&Play\tCtrl-P", "Play or pause track");
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
	menuBar->Append(libraryMenu, "&Library");
	menuBar->Append(controlMenu, "&Controls");
	menuBar->Append(playListMenu, "&Playlist");
	menuBar->Append(helpMenu, "&Help");
	SetMenuBar(menuBar);

	//bind all menu events
	Bind(wxEVT_MENU, &MainFrame::OnDir, this,
		ID_DIR);
	Bind(wxEVT_MENU, &MainFrame::OnScan, this,
		ID_SCAN);
	Bind(wxEVT_MENU, &MainFrame::OnExit, this,
		wxID_EXIT);

	Bind(wxEVT_MENU, &MainFrame::OnTitle, this,
		ID_TITLE);
	Bind(wxEVT_MENU, &MainFrame::OnAlbum, this,
		ID_ALBUM);
	Bind(wxEVT_MENU, &MainFrame::OnArtist, this,
		ID_ARTIST);

	Bind(wxEVT_MENU, &MainFrame::OnNext, this,
		ID_NEXT);
	Bind(wxEVT_MENU, &MainFrame::OnPrev, this,
		ID_PREV);
	Bind(wxEVT_MENU, &MainFrame::OnLoop, this,
		ID_LOOP);
	Bind(wxEVT_MENU, &MainFrame::OnLoopList, this,
		ID_LOOPALL);

	Bind(wxEVT_MENU, &MainFrame::OnSave, this,
		ID_SAVE);
	Bind(wxEVT_MENU, &MainFrame::OnLoad, this,
		ID_LOAD);

	Bind(wxEVT_MENU, &MainFrame::OnAbout, this,
		wxID_ABOUT);
}

/*setups up the tool bar*/
void MainFrame::initToolBar()
{
	toolBar = new wxToolBar(this, wxID_ANY,
		wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxNO_BORDER | wxTB_BOTTOM);

	volSlider = new wxSlider(toolBar, ID_VOL_SLIDER, 100, 0, 100,
		wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);

	toolBar->AddControl(volSlider);

	//load icons for toolbar
	wxInitAllImageHandlers();
	wxBitmap bmpPlay(wxT("Resources/play.png"), wxBITMAP_TYPE_PNG);
	if (!bmpPlay.Ok()) { wxMessageBox(wxT("Sorry, could not load file.")); }
	wxBitmap bmpPrev(wxT("Resources/prev.png"), wxBITMAP_TYPE_PNG);
	if (!bmpPlay.Ok()) { wxMessageBox(wxT("Sorry, could not load file.")); }
	wxBitmap bmpNext(wxT("Resources/next.png"), wxBITMAP_TYPE_PNG);
	if (!bmpPlay.Ok()) { wxMessageBox(wxT("Sorry, could not load file.")); }

	toolBar->AddTool(ID_PREV, wxT("prev"), bmpPrev, "play previous");
	toolBar->AddTool(ID_PLAY, wxT("Play"), bmpPlay, "start/stop track");
	toolBar->AddTool(ID_NEXT, wxT("next"), bmpNext, "play next");

	timeSlider = new wxSlider(toolBar, ID_TIME_SLIDER, 0, 0, 10,
		wxDefaultPosition, wxSize(200, -1), wxSL_HORIZONTAL);

	toolBar->AddControl(timeSlider);
	toolBar->Realize();

	SetToolBar(toolBar);

	//Bind all tool bar events
	Bind(wxEVT_COMMAND_SLIDER_UPDATED, &MainFrame::OnSlider, this, ID_VOL_SLIDER);
	Bind(wxEVT_COMMAND_SLIDER_UPDATED, &MainFrame::OnTimeSlider, this, ID_TIME_SLIDER);
	Bind(wxEVT_COMMAND_SCROLLBAR_UPDATED, &MainFrame::OnTimeSlider, this, ID_VOL_SLIDER);
	
	Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::OnPlay, this,
		ID_PLAY);
	Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::OnNext, this,
		ID_NEXT);
	Bind(wxEVT_COMMAND_TOOL_CLICKED, &MainFrame::OnPrev, this,
		ID_PREV);
	
}

void MainFrame::setCurrTrack(Node *track)
{
	if (isTrackLoop())
	{
		mFile->seek(0);
		audio->resetCounter();
	}
	else if (track != nullptr)
	{
		audio->clearBuffer();
		audio->stopStream();
		currTrackPTR = track;
		delete mFile;
		mFile = new MusicFile(currTrackPTR->track->path);
		audio->resetCounter();
		audio->openStream(mFile->getNumChannels(), mFile->getBitsPerSample(), mFile->getSampleRate());
		audio->startStream();
		statusBar->SetStatusText(currTrackPTR->track->title, 1);
		timeSlider->SetRange(0, mFile->getDataSize());
		misPlaying = true;
	}
	else
	{
		audio->stopStream();
	}
}

void MainFrame::OnTimer(wxTimerEvent &WXUNUSED(event))
{
	//TODO check if there is a activated track or playlist is empty
	if (misPlaying)
	{
		//True if audio data was successfully passed to the audio stream
		bool success = audio->playAudio(mFile);
		if (!success)
		{
			if (audio->getErr() != 0) //unrecoverable error (TODO handle more errors)
			{
				timer->Stop();
				wxMessageBox(audio->getErrorMessage());
				audio->Terminate();
				Close(true);
			}
			else //end of track reached
			{
				if (currTrackPTR != nullptr)
				{
					setCurrTrack(currTrackPTR->next);
				}
			}
		}
		else //update time slider and status
		{
			string time = mFile->timeToString(audio->getCounter());
			timeSlider->SetValue(audio->getCounter() * 4);
			statusBar->SetStatusText(time, 2);
		}
	}
}

void MainFrame::OnExit(wxCommandEvent &WXUNUSED(event))
{
	timer->Stop();
	Close(true);
}
void MainFrame::OnDir(wxCommandEvent &WXUNUSED(event))
{
	wxString def = wxT("/");
	wxDirDialog dir(this, wxT("Select Library Loction"), def);
	if (dir.ShowModal() == wxID_OK)
	{
		mLibraryPath = dir.GetPath() + '/';
		wxMessageBox(mLibraryPath);
	}
}
void MainFrame::OnScan(wxCommandEvent &WXUNUSED(event))
{
	wxDir dir(mLibraryPath);
	if (!dir.IsOpened())
	{
		wxMessageBox(wxT("Sorry, could not open directory."));
		return;
	}
	wxString fileName;
	wxString fileType = "*.wav*";

	bool cont = dir.GetFirst(&fileName, fileType, wxDIR_FILES | wxDIR_DIRS);
	while (cont)
	{
		string file = string(fileName.mb_str());
		readWavInfo(mLibraryPath + file);
		cont = dir.GetNext(&fileName);
	}
}

void MainFrame::OnTitle(wxCommandEvent &WXUNUSED(event))
{
	mPanel->recreateList(00);
}
void MainFrame::OnAlbum(wxCommandEvent &WXUNUSED(event))
{
	mPanel->recreateList(10);
}
void MainFrame::OnArtist(wxCommandEvent &WXUNUSED(event))
{
	mPanel->recreateList(20);
}
void MainFrame::OnPlay(wxCommandEvent &WXUNUSED(event))
{
	misPlaying = !misPlaying;
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

void MainFrame::OnLoad(wxCommandEvent &WXUNUSED(event))
{
	loadCurrPlayList("Data/");
}

void MainFrame::OnAbout(wxCommandEvent &WXUNUSED(event))
{
	wxString message("Medea Music Player: \nBy Eric Woodard for cs151\nA simple wav player\nThanks to icon king1 for the icons!\nFrom: https://freeicons.io/icon-list/material-icons-alert-and-av?page=1 \n\nLibrarys used:\nPortaudio\nwxWidgets\n");
	wxMessageBox(message);
}

void MainFrame::OnSlider(wxCommandEvent &WXUNUSED(event))
{
	audio->setVolume(volSlider->GetValue() / 100.0f);
}

void MainFrame::OnTimeSlider(wxCommandEvent &WXUNUSED(event))
{
	audio->stopStream();

	//taken from https://wiki.wxwidgets.org/WxSlider_step_intervals
	int val = timeSlider->GetValue();

	int remainder = val % audio->getFramesPerBuffer(); // The step interval.

	// If the value is not evenly divisible by the step interval,
	// snap the value to an even interval.
	if (remainder != 0) {
		val -= remainder;
		timeSlider->SetValue(val);
	}

	audio->setCounter(timeSlider->GetValue() / 4);
	mFile->seek(timeSlider->GetValue());
	audio->clearBuffer();
	audio->startStream();
}

void MainFrame::saveCurrPlaylist(string path)
{
	Node *ptr = mPanel->getFront();
	fstream outFile(path + mPanel->getListName(), ios_base::out);
	if (!outFile)
	{
		wxMessageBox(wxT("Could not load file." + mPanel->getListName()));
		return;
	}

	while (ptr->next != nullptr)
	{
		outFile << ptr->track->title << ',' << ptr->track->album << ','
			<< ptr->track->artist << ',' << ptr->track->year << ','
			<< ptr->track->genre << ',' << ptr->track->trackNumber << ','
			<< ptr->track->length << ',' << ptr->track->rating << ','
			<< ptr->track->timesPlayed << ',' << ptr->track->path << '\n';
		ptr = ptr->next;
	}
	
	outFile << ptr->track->title << ',' << ptr->track->album << ','
		<< ptr->track->artist << ',' << ptr->track->year << ','
		<< ptr->track->genre << ',' << ptr->track->trackNumber << ','
		<< ptr->track->length << ',' << ptr->track->rating << ','
		<< ptr->track->timesPlayed << ',' << ptr->track->path;
}

void MainFrame::loadCurrPlayList(string path)
{
	wxFileDialog dialog(this);

	if (!dialog.ShowModal() == wxID_OK)
	{
		//error
	}
	wxString str = dialog.GetPath();
	string fileName = string(str.mb_str());
	mPanel->clearPlaylist();
	ifstream inFile(fileName);
	if (!inFile)
	{
		wxMessageBox(wxT("Sorry, could not open playlist."));
		return;
	}
	masterPlayList->clear();

	while (!inFile.eof())
	{
		Track track;
		char del;
		getline(inFile, track.title, ',');
		getline(inFile, track.album, ',');
		getline(inFile, track.artist, ',');
		inFile >> track.year;
		inFile >> del;
		getline(inFile, track.genre, ',');
		inFile >> track.trackNumber;
		inFile >> del;
		inFile >> track.length;
		inFile >> del;
		inFile >> track.rating;
		inFile >> del;
		inFile >> track.timesPlayed;
		inFile >> del;
		getline(inFile, track.path);
		
		masterPlayList->addRear(&(*mLibrary)[searchByTitle(*mLibrary, track.title)]);
	}

	mPanel->setPlaylist(&masterPlayList);
	Node *ptr = masterPlayList->front();
	setCurrTrack(ptr);
}
void MainFrame::readWavInfo(const string &path)
{
	Track track;
	track.path = path;
	fstream inFile(path, ios::in | ios::binary);
	if (!inFile)
	{
		wxMessageBox(wxT("Sorry, could not open wave file."));
		return;
	}
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
			if (track.title[0] == '0' || track.title[0] == '1')
			{
				track.title.erase(0, 3);
			}
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
	mLibrary->push_back(track);
}

void MainFrame::saveMasterList()
{
	fstream outFile("Data/masterList.csv", ios::out);
	if (!outFile)
	{
		wxMessageBox(wxT("Sorry, could not open wave file."));
		return;
	}
	for (int i = 0; i < mLibrary->size(); ++i)
	{
		outFile << (*mLibrary)[i].title << ',' << (*mLibrary)[i].album << ','
			<< (*mLibrary)[i].artist << ',' << (*mLibrary)[i].year << ','
			<< (*mLibrary)[i].genre << ',' << (*mLibrary)[i].trackNumber << ','
			<< (*mLibrary)[i].length << ',' << (*mLibrary)[i].rating << ','
			<< (*mLibrary)[i].timesPlayed << ',' << (*mLibrary)[i].path;

		if (i != mLibrary->size() - 1)
		{
			outFile << '\n';
		}
	}
	
	outFile.close();
	
}

void advanceToNextTag(fstream &inFile)
{
	char delem;
	while (inFile.peek() == '\0')
	{
		inFile.get(delem);
	}
}

