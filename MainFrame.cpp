/**********************************************************************
 Medea: A Digital Music Player

 @file  MainFrame.cpp

 @brief:

 Manages the file menus, toolbar, statusbar, child panels,
 and communicates with audio and file managers.

 @author Eric Woodard
 @date   12/11/2020

 **********************************************************************/
#include "MainFrame.h"
/*
* MainFrame constructor
* 
* @param size the size of the window
* @param masterVec the master library that contians all audio track
* @param albumIndex the library indexed by album
* @param artistIndex the library index by artist
*/
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
	misPlaying = false;

	//sets icon in top corner
	SetIcon(wxICON(icon));
	
	initMenu();

	mParent = new wxPanel(this, wxID_ANY);
	mLibraryPanel = new LibraryPanel(mParent, mLibrary, *mAlbumIndex, *mArtistIndex);
	mPlaylistPanel = new PlaylistPanel(mParent);
	hbox = new wxBoxSizer(wxHORIZONTAL);
	hbox->Add(mLibraryPanel, wxSizerFlags(2).Expand().Border());
	hbox->Add(mPlaylistPanel, wxSizerFlags(2).Expand().Border());
	mParent->SetSizer(hbox);
	this->Center();

	initToolBar();
	statusBar = new wxStatusBar(this, wxID_ANY);
	SetStatusBar(statusBar);
	statusBar->SetFieldsCount(3);
	statusBar->SetStatusText(wxT("Ready"), 0);

	timer = new wxTimer(this, 1);
	Bind(wxEVT_TIMER, &MainFrame::OnTimer, this);
	
	timer->Start(10);
	
}
void MainFrame::setThread(string path)
{
	mThread = new AudioThread(path, timeSlider);
	if (mThread->Create() != wxTHREAD_NO_ERROR)
	{
		wxMessageBox(wxT("Can't create thread"));
	}
	mThread->Run();
}
/*
* default destructor
*/
MainFrame::~MainFrame()
{
	///It is important to stop the timer otherwise wxWidgets throws an exception
	timer->Stop();
	
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
	controlMenu->Append(ID_STOP, "&Stop\tCtrl-O", "Stop current track");
	controlMenu->Append(ID_NEXT, "&Next\tCtrl-N", "Skip to next track");
	controlMenu->Append(ID_PREV, "&Previous\tCtrl-B", "Skip to previous track");
	controlMenu->AppendSeparator();
	controlMenu->Append(ID_LOOP, "&Loop\tCtrl-L", "Loop current track");
	controlMenu->Append(ID_LOOPALL, "Loop &All\tCtrl-K", "Loop current playlist");

	playListMenu->Append(ID_SAVE, "&Save\tCtrl-S", "Save current playlist");
	playListMenu->Append(ID_LOAD, "Loa&d\tCtrl-D", "Load a playlist");
	playListMenu->Append(ID_CLEAR, "&Clear\tAlt-C", "Clear the playlist");

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

	Bind(wxEVT_MENU, &MainFrame::OnPlay, this,
		ID_PLAY);
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
	Bind(wxEVT_MENU, &MainFrame::OnClear, this,
		ID_CLEAR);

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
/*
* sets a track to be read and played
* 
* @param track the node that contains a pointer to the track
*/
void MainFrame::setCurrTrack(Node *track)
{
	if (isTrackLoop())
	{
		setThread(currTrackPTR->track->path);
	}
	else if (track != nullptr)
	{
		
		if (currTrackPTR != nullptr)
		{
			mPlaylistPanel->focusTrack(currTrackPTR->track, track->track);
		}
		else
		{
			mPlaylistPanel->focusTrack(track->track);
		}

		currTrackPTR = track;
		
		if (mThread == nullptr)
		{
			setThread(currTrackPTR->track->path);
		}
		else
		{
			mThread->Delete();
			setThread(currTrackPTR->track->path);
			//mThread->setPath(currTrackPTR->track->path);
		}

		statusBar->SetStatusText(currTrackPTR->track->title, 1);
		if (!misPlaying)
		{
			toggleisPlaying();
		}
	}
}
/*
* called after an interval of microseconds passes
* used to play audio
*
* @param event the timer event being caught
*/
void MainFrame::OnTimer(wxTimerEvent &WXUNUSED(event))
{
	//TODO check if there is a activated track or playlist is empty
	long max = timeSlider->GetMax();
	long curr = timeSlider->GetValue();
	//file->getDataSize() - (mFrameCounter * file->getBlockAlighn()) >= mFramesPerBuffer * 3
	if (mThread != nullptr)
	{
		if (mThread->isOver())
		{
			setCurrTrack(currTrackPTR->next);
		}
		else //update time slider and status
		{
			timeSlider->SetValue(mThread->getCounter() * 4);
			long bytes = timeSlider->GetValue();

			int n = bytes / (44100 * 2 * 16 / 8);
			int min = n / 60;
			n = n % 60;
			int sec = n;
			std::ostringstream stream;
			std::string trackTime;

			stream << min << ':';
			if (sec < 10)
				stream << 0 << sec;
			else
				stream << sec;

			statusBar->SetStatusText(stream.str(), 2);
		}
	}
	
}
/*
* called when exit menu clicked
* Closes the program
* 
* @param event the menu event being caught
*/
void MainFrame::OnExit(wxCommandEvent &WXUNUSED(event))
{
	timer->Stop();
	Close(true);
}
/*
* called when set dir menu clicked
* Opens a dialog to select a path to music library on the computer
*
* @param event the menu event being caught
*/
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
/*
* called when scan menu clicked
* scans library directory and adds track to master library
*
* @param event the menu event being caught
*/
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

	saveMasterList();
}
/*
* called when sort by title menu clicked
* Triggers the program to sort by title
*
* @param event the menu event being caught
*/
void MainFrame::OnTitle(wxCommandEvent &WXUNUSED(event))
{
	mLibraryPanel->toggleByTitle();
	mLibraryPanel->recreateList();
}
/*
* called when sort by album menu clicked
* Triggers the program to sort by album 
*
* @param event the menu event being caught
*/
void MainFrame::OnAlbum(wxCommandEvent &WXUNUSED(event))
{
	mLibraryPanel->toggleByAlbum();
	mLibraryPanel->recreateList();
}
/*
* called when sort by artist menu clicked
* Triggers the program to sort by artist
*
* @param event the menu event being caught
*/
void MainFrame::OnArtist(wxCommandEvent &WXUNUSED(event))
{
	mLibraryPanel->toggleByArtist();
	mLibraryPanel->recreateList();
}
void MainFrame::toggleisPlaying()
{
	if (currTrackPTR == nullptr)
	{
		return;
	}
	misPlaying = !misPlaying;
	if (!misPlaying)
	{
		mThread->Pause();
	}
	else
	{
		mThread->Resume();
	}
}
/*
* called when play menu clicked
* Toggles the audio stream to start/stop
*
* @param event the menu event being caught
*/
void MainFrame::OnPlay(wxCommandEvent &WXUNUSED(event))
{
	toggleisPlaying();
}

/*
* called when next menu clicked
* calls currTrack to the next node in the playlist
*
* @param event the menu event being caught
*/
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
			//setCurrTrack(mLibraryPanel->);
		}
	}
}
/*
* called when prev menu clicked
* calls currTrack to the previous node in the playlist
*
* @param event the menu event being caught
*/
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
			//setCurrTrack(masterPlayList->rear());
		}
	}
}
/*
* called when loop menu clicked
* toggles loopTrack
*
* @param event the menu event being caught
*/
void MainFrame::OnLoop(wxCommandEvent &WXUNUSED(event))
{
	toggleLoopTrack();
}
/*
* called when loop all menu clicked
* toggles loopAll
*
* @param event the menu event being caught
*/
void MainFrame::OnLoopList(wxCommandEvent &WXUNUSED(event))
{
	toggleLoopList();
}
/*
* called when save menu clicked
* saves playlist to a file
*
* @param event the menu event being caught
*/
void MainFrame::OnSave(wxCommandEvent &WXUNUSED(event))
{
	mPlaylistPanel->saveCurrPlaylist("Data/");
}
/*
* called when Load menu clicked
* Loads a playlist from a file
*
* @param event the menu event being caught
*/
void MainFrame::OnLoad(wxCommandEvent &WXUNUSED(event))
{
	loadCurrPlayList("Data/");
}
/*
* called when clear menu clicked
* clears the current playlist
*
* @param event the menu event being caught
*/
void MainFrame::OnClear(wxCommandEvent &WXUNUSED(event))
{
	mPlaylistPanel->clearPlaylist();
}
/*
* called when about menu clicked
* Creates a popup dialog to dispaly program info
*
* @param event the menu event being caught
*/
void MainFrame::OnAbout(wxCommandEvent &WXUNUSED(event))
{
	wxString message("Medea Music Player: \nBy Eric Woodard for cs151\nA simple wav player\nThanks to icon king1 for the icons!\nFrom: https://freeicons.io/icon-list/material-icons-alert-and-av?page=1 \n\nLibrarys used:\nPortaudio\nwxWidgets\n");
	wxMessageBox(message);
}
/*
* called when volume slider moved
* sets the audio volume
*
* @param event unused for backwards compatibility
*/
void MainFrame::OnSlider(wxCommandEvent &WXUNUSED(event))
{
	mThread->setVolume(volSlider->GetValue() / 100.0f);
}
/*
* called when timer slider moved
* seeks throug the audio file
*
* @param event unused for backwards compatibility
*/
void MainFrame::OnTimeSlider(wxCommandEvent &WXUNUSED(event))
{
	//taken from https://wiki.wxwidgets.org/WxSlider_step_intervals
	int val = timeSlider->GetValue();

	int remainder = val % 2048; // The step interval.

	 //If the value is not evenly divisible by the step interval,
	 //snap the value to an even interval.
	if (remainder != 0) 
	{
		val -= remainder;
		timeSlider->SetValue(val);
	}
	
	mThread->setFilePos(val);
}
/*
* loads a playlist from a file
*
* @param path the location of the playlist on the computer
*/
void MainFrame::loadCurrPlayList(string path)
{
	wxFileDialog dialog(this);

	if (!dialog.ShowModal() == wxID_OK)
	{
		wxMessageBox(wxT("Sorry, could not open dialog."));
	}
	wxString str = dialog.GetPath();
	string filePath = string(str.mb_str());

	mPlaylistPanel->clearPlaylist();
	ifstream inFile(filePath);
	if (!inFile)
	{
		wxMessageBox(wxT("Sorry, could not open playlist."));
		return;
	}

	while (!inFile.eof())
	{
		Track track;
		getline(inFile, track.title, ',');
		getline(inFile, track.album, ',');
		getline(inFile, track.path);
		mPlaylistPanel->appendTrack(&(*mLibrary)[searchByTitle(*mLibrary, track.title)]);
	}
}
/*
* reads wav header and tag info from a file. Then adds a new track to the master library.
* Used while scanning music library directory
*
* @param path the location of the library directory on the computer
*/
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
/*
* save the masterList as a csv file
*/
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
/*
* reads the empty space after a tag until the next tag is found
*/
void advanceToNextTag(fstream &inFile)
{
	char delem;
	while (inFile.peek() == '\0')
	{
		inFile.get(delem);
	}
}