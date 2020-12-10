#ifndef PLAYLISTCTRL_H
#define PLAYLISTCTRL_H

#include <wx/listctrl.h>
#include "Playlist.h"

class PlayListCtrl : public wxListView
{
public:
	PlayListCtrl(wxWindow *parent, wxWindowID id);
	void addList(Playlist &list);
	void addTrack(Node *node, long index);
	void removeTrack(long index);
private:
	
};


#endif