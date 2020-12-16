#include "PlayListCtrl.h"

PlayListCtrl::PlayListCtrl(wxWindow *parent, wxWindowID id)
	: wxListView(parent, ID_LIST, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_HRULES)
{ 
	//Add columns to Ctrl list        
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

void PlayListCtrl::updateListView(const Playlist &list)
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

void PlayListCtrl::addTrack(Track *track, long index)
{
	wxString i = wxString::Format(wxT("%i"), index);
	long itemIndex = InsertItem(index, i); //want this for col. 1
	SetItem(itemIndex, 1, track->title); //want this for col. 2
	SetItem(itemIndex, 2, track->album); //want this for col. 2
}

void PlayListCtrl::appendTrack(const Track *track)
{
	long index = GetItemCount();
	long itemIndex = InsertItem(index, index); //want this for col. 1
	SetItem(itemIndex, 1, track->title); //want this for col. 2
	SetItem(itemIndex, 2, track->album); //want this for col. 2
}
void PlayListCtrl::removeTrack(long index)
{
	DeleteItem(index);
}


