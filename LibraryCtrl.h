/**********************************************************************
 Medea: A Digital Music Player

 @file  LibraryCtrl.h

 @brief:

 Populates and displays music library to a list on the screen

 @author Eric Woodard
 @date   12/11/2020

 TODO: Display proper track duration
 **********************************************************************/
#ifndef LIBRARYCTRL_H
#define LIBRARYCTRL_H

#include "Playlist.h"
#include <wx/listctrl.h>
#include <vector>

using std::vector;

class LibraryCtrl : public wxListView
{
public:
	LibraryCtrl(wxWindow *parent, wxWindowID id);
	void addList(const vector<Track> &vec, const bool reversed);
	void addList(const vector<Track*> &vec, const bool reversed);

private:

};

#endif

