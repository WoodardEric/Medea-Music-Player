/**********************************************************************
 Medea: A Digital Music Player

 @file  PlaylistPanel.h

 @brief:

 holds playlistCtrl, syncs the playlist with the listCtrl, manages the
 spacing of the playlistCtrl on frame, and catches playlistCtrl events.

 @author Eric Woodard
 @date   12/11/2020

 TODO: have PlaylistCtrl display list index next to track name
 **********************************************************************/
#ifndef PLAYLISTPANEL_H
#define PLAYLISTPANEL_H

#include "PlayListCtrl.h"
#include "Playlist.h"

#include <wx/wx.h>

class PlaylistPanel : public wxPanel
{
public:
	PlaylistPanel(wxPanel *parent);

	void OnAtivate(wxListEvent &event);
	void OnRightClick(wxListEvent &event);
	void OnPopupClick(wxCommandEvent &event);
	
	int getPlaylistSize() const { return mPlaylist.size(); }

	void appendTrack(Track *track);
	void removeTrack(long index);

	void focusTrack(const Track *currTrack, const Track *nextTrack);
	void focusTrack(const Track *track);

	void saveCurrPlaylist(string path);
	void clearPlaylist();
	
	
private:
	long mFirstIndex; //index of track node that user selects to move.
	Node *mPTRMove; //copy of the node being moved

	wxPanel *mParent; //parent wxPanel to allow communication from child
	wxBoxSizer *mSizer; //manages mPlaylistCtrl spacing on window resize

	Playlist mPlaylist; //linked list of tracks
	PlaylistCtrl *mPlaylistCtrl; //displays mPlaylist to screen
	
};

#endif