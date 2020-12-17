/**********************************************************************
 Medea: A Digital Music Player

 @file  PlaylistCtrl.h

 @brief:

 Adds and removes playlist for the listCtrl and displays playlist
 track info to the screen as a list.

 @author Eric Woodard
 @date   12/11/2020

 **********************************************************************/

#include "PlayListCtrl.h"

/*
* PlaylistCtrl constructor
*
* @param *parent pointer to parent panel
*/
PlaylistCtrl::PlaylistCtrl(wxWindow *parent)
	: wxListView(parent, ID_LIST, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_HRULES)
{ 
	//Add columns to ListView       
	wxListItem playlistNum;
	playlistNum.SetId(0);
	playlistNum.SetText(_("#"));
	playlistNum.SetWidth(25);
	InsertColumn(0, playlistNum);
      
	wxListItem titleCol;
	titleCol.SetId(1);
	titleCol.SetText(_("Title"));
	titleCol.SetWidth(100);
	InsertColumn(1, titleCol);

	wxListItem albumCol;
	albumCol.SetId(2);
	albumCol.SetText(_("Album"));
	albumCol.SetWidth(100);
	InsertColumn(2, albumCol);

}
/*
* repopulates PlaylistCtrl
*
* @param &list playlist being added to PlaylistCtrl
*/
void PlaylistCtrl::updateListView(const Playlist &list)
{
	Node *ptr = list.front();
	
	while (ptr != nullptr)
	{
		wxString i = wxString::Format(wxT("%i"), ptr->track->trackNumber);
		long itemIndex = InsertItem(0, i); //want this for col. 1
		SetItem(itemIndex, 1, ptr->track->title); //want this for col. 2
		SetItem(itemIndex, 2, ptr->track->album); //want this for col. 2
		ptr = ptr->prev;
	}
}

/*
* adds a track at specific index to the PlaylistCtrl
*
* @param *track that is being added to PlaylistCtrl
* @param index location of where track is being inserted
*/
void PlaylistCtrl::addTrack(const Track *track, const long index)
{
	wxString i = wxString::Format(wxT("%i"), index);
	long itemIndex = InsertItem(index, i); //want this for col. 1
	SetItem(itemIndex, 1, track->title); //want this for col. 2
	SetItem(itemIndex, 2, track->album); //want this for col. 2
}
/*
* adds a track to end of the PlaylistCtrl
*
* @param *track that is being added to PlaylistCtrl
*/
void PlaylistCtrl::appendTrack(const Track *track)
{
	long index = GetItemCount();
	long itemIndex = InsertItem(index, index); //want this for col. 1
	SetItem(itemIndex, 1, track->title); //want this for col. 2
	SetItem(itemIndex, 2, track->album); //want this for col. 2
}
/*
* removes a track from the playlist at a specific index
*
* @param index location of where track is being deleted
*/
void PlaylistCtrl::removeTrack(const long index)
{
	DeleteItem(index);
}


