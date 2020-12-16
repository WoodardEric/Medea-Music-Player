#ifndef PLAYLISTCTRL_H
#define PLAYLISTCTRL_H

#include "IDs.h"
#include "Playlist.h"

#include <wx/wx.h>
#include <wx/listctrl.h>

#include <string>
#include <fstream>

using std::string;
using std::ifstream;

class PlayListCtrl : public wxListView
{
public:
	PlayListCtrl(wxWindow *parent, wxWindowID id);
	
	void updateListView(const Playlist &list);
	void addTrack(Track *track, long index);
	void appendTrack(const Track *track);
	void removeTrack(long index);
	
private:
};

#endif