#ifndef PLAYLISTCTRL_H
#define PLAYLISTCTRL_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "IDs.h"
#include "Playlist.h"
#include <string>
#include <fstream>

using std::string;
using std::ifstream;

class PlayListCtrl : public wxListView
{
public:
	PlayListCtrl(wxWindow *parent, wxWindowID id, Playlist **list);
	void setPlaylist(Playlist **list);
	void updateListView();
	void addTrack(Track *track, long index);
	void appendTrack(Track *track);
	void removeTrack(long index);
	Node *front() const { return mPlaylist->front(); }
	string getName() const { return mPlaylist->getName(); }
	Node *traverse(long index) { return mPlaylist->traverse(index); }
	void clearPlayList() { mPlaylist->clear(); }
	void loadPlayListFile(string path);
	void move(Node *node, long index);
	
    void OnPopupClick(wxCommandEvent &event);
    void OnRightClick(wxListEvent &event);

private:
	Node *mPTRMove;
	Playlist *mPlaylist;
	long mFirstIndex;

};


#endif