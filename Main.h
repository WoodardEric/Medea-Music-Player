/**********************************************************************
 Medea: A Digital Music Player

 @file  Main.h

 @brief:

 Main.h initilizes program data and sets up the main window. 
 This is were the program would read any int file if implemented.

 @author Eric Woodard
 @date   12/11/2020

 Priority TODO:
 *Find less arbitrary way to fix pop at end of track(almost certain it is
  tag info being read into audio stream)
 *Handle current track being removed from playlist
 *Highligt current track in playlistCtrl
 *figure out better buffering method/handle reading audio file 
  on different thread
 **********************************************************************/
#ifndef MAIN_H
#define MAIN_H

#include "index.h"
#include "MainFrame.h"

// For compilers that support precompilation, includes "wx.h".
#include <wx/wxprec.h>
#ifdef __BORLANDC__
#   pragma hdrstop
#endif
#ifndef WX_PRECOMP
	// Include your minimal set of headers here, or wx.h
#   include <wx/wx.h>
#endif

#include <vector>

class MedeaApp : public wxApp
{
public:
	void initMasterLibrary();
	bool OnInit();
	vector<Track> masterLibrary;
	vector<Track *> mAlbumIndex;
	vector<Track *> mArtistIndex;

};

#endif

