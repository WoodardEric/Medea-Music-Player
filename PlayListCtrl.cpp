#include "PlayListCtrl.h"

PlayListCtrl::PlayListCtrl(wxWindow *parent, wxWindowID id)
	: wxListView(parent, id, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_HRULES)
{ 

	// Add first column        
	wxListItem col0;
	col0.SetId(0);
	col0.SetText(_("#"));
	col0.SetWidth(25);
	InsertColumn(0, col0);

	// Add first column        
	wxListItem col1;
	col1.SetId(1);
	col1.SetText(_("Title"));
	col1.SetWidth(100);
	InsertColumn(1, col1);

	// Add second column 
	wxListItem col2;
	col2.SetId(2);
	col2.SetText(_("Album"));
	col2.SetWidth(100);
	InsertColumn(2, col2);
}



void PlayListCtrl::addList(Playlist &list)
{
	Node *ptr = list.rear();
	int index = list.size();
	while (ptr != nullptr)
	{
		wxString i = wxString::Format(wxT("%i"), index);
		long itemIndex = InsertItem(0, i); //want this for col. 1
		SetItem(itemIndex, 1, ptr->track->title); //want this for col. 2
		SetItem(itemIndex, 2, ptr->track->album); //want this for col. 2
		ptr = ptr->prev;
		--index;
	}
}
void PlayListCtrl::addTrack(Node *node, long index)
{
	wxString i = wxString::Format(wxT("%i"), index);
	long itemIndex = InsertItem(index, i); //want this for col. 1
	SetItem(itemIndex, 1, node->track->title); //want this for col. 2
	SetItem(itemIndex, 2, node->track->album); //want this for col. 2
}
void PlayListCtrl::removeTrack(long index)
{
	DeleteItem(index);
}
//Node *findNodeFromIndex(Node *ptr, long index)
//{
//	for (int i = 0; i < index; ++i)
//	{
//		ptr = ptr->next;
//	}
//
//	return ptr;
//}