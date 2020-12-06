#ifndef PLAYLISTCTRL_H
#define PLAYLISTCTRL_H

#include <wx/listctrl.h>
#include "Playlist.h"

class PlayListCtrl : public wxListView
{
public:
	PlayListCtrl(wxWindow *parent);

private:
	Playlist *mPlayList;
};


#endif