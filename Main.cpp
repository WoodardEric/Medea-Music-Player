/**********************************************************************
 Medea: A Digital Music Player

 @file  Main.cpp

 @brief:

 Main.ccp initilizes program data and sets up the main window. 
 This is were the program would read any int file if implemented.

 @author Eric Woodard
 @date   12/11/2020
 **********************************************************************/
#include "Main.h"

//macro that sets up the main function, makes an instance of MedeApp, and calls OnInit
IMPLEMENT_APP(MedeaApp);

/*
* acts as main function. Creates the main window and initializes the music library
*/
bool MedeaApp::OnInit()
{
	initMasterLibrary();
		
    MainFrame *main = new MainFrame(wxSize(1200, 600), masterLibrary, mAlbumIndex, mArtistIndex);
    main->Show(true);
    SetTopWindow(main);

    return true;
}

/*
* creates the master library from a file then creates the indexes
*/
void MedeaApp::initMasterLibrary()
{
	fstream inFile("Data/masterList.csv", ios::in);
	if (!inFile)
	{
		wxMessageBox(wxT("Sorry, could not open master library."));
		return;
	}

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

		masterLibrary.push_back(track);
	}

	attachIndexToVector(mAlbumIndex, masterLibrary);
	attachIndexToVector(mArtistIndex, masterLibrary);
	sortByTitle(masterLibrary);
	sortByAlbum(mAlbumIndex);
	sortByArtist(mArtistIndex);
}