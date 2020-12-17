/**********************************************************************
 Medea: A Digital Music Player

 @file  PlaylistCtrl.h

 @brief:

 Adds and removes playlist for the listCtrl and displays playlist 
 track info to the screen as a list.

 @author Eric Woodard
 @date   12/11/2020

 **********************************************************************/
#ifndef PLAYLISTCTRL_H
#define PLAYLISTCTRL_H

#include "IDs.h"
#include "Playlist.h"

#include <wx/wx.h>
#include <wx/listctrl.h>

//#include <fstream>
//#include <string>

//using std::ifstream;
//using std::string;

class PlaylistCtrl : public wxListView
{
public:
	PlaylistCtrl(wxWindow *parent);
	
	void updateListView(const Playlist &list);
	void addTrack(const Track *track, const long index);
	void appendTrack(const Track *track);
	void removeTrack(const long index);
	
private:
};

#endif