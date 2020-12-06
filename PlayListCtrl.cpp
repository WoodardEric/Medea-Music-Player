#include "PlayListCtrl.h"

PlayListCtrl::PlayListCtrl(wxWindow *parent) 
	: wxListView(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_HRULES)
{
	mPlayList = new Playlist();
	
	// Add first column        
	wxListItem col0;
	col0.SetId(0);
	col0.SetText(_("Title"));
	col0.SetWidth(300);
	InsertColumn(0, col0);

	// Add second column 
	wxListItem col1;
	col1.SetId(1);
	col1.SetText(_("Album"));
	col1.SetWidth(50);
	InsertColumn(1, col1);

	Node *ptr = mPlayList->front();
	while (ptr != nullptr)
	{
		long itemIndex = InsertItem(0, ptr->track.song); //want this for col. 1
		SetItem(itemIndex, 1, ptr->track.album); //want this for col. 2
		ptr = ptr->next;
	}
}
