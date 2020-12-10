#include "PlayListCtrl.h"

PlayListCtrl::PlayListCtrl(wxWindow *parent, wxWindowID id, Playlist **list)
	: wxListView(parent, ID_LIST, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_HRULES),
	mPlaylist (*list)
{ 
	Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &PlayListCtrl::OnRightClick, this, ID_LIST);
	

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

	updateListView();
}
void PlayListCtrl::setPlaylist(Playlist **list)
{
	mPlaylist = *list;
	updateListView();
}
void PlayListCtrl::updateListView()
{
	Node *ptr = mPlaylist->rear();
	
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

void PlayListCtrl::appendTrack(Track *track)
{
	mPlaylist->addRear(track);
	long index = GetItemCount();
	long itemIndex = InsertItem(index, "1"); //want this for col. 1
	SetItem(itemIndex, 1, track->title); //want this for col. 2
	SetItem(itemIndex, 2, track->album); //want this for col. 2
}
void PlayListCtrl::removeTrack(long index)
{
	DeleteItem(index);
}
void PlayListCtrl::move(Node *node, long index)
{
	mPlaylist->move(node, index);
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
void PlayListCtrl::loadPlayListFile(string path)
{
	ifstream inFile(path);
	if (!inFile)
	{
		wxMessageBox(wxT("Sorry, could not open playlist."));
		return;
	}

	while (!inFile.eof())
	{
		Track track;
		char del;
		getline(inFile, track.title, ',');
		getline(inFile, track.album, ',');
		getline(inFile, track.artist, ',');
		inFile >> track.year;
		inFile >> del;
		getline(inFile, track.genre, ',');
		inFile >> track.trackNumber;
		inFile >> del;
		inFile >> track.length;
		inFile >> del;
		inFile >> track.rating;
		inFile >> del;
		inFile >> track.timesPlayed;
		inFile >> del;
		getline(inFile, track.path);

		mPlaylist->addRear(&track);
	}
}
void PlayListCtrl::OnPopupClick(wxCommandEvent &event)
{

	int offset = 0;
	int index = -1;
	switch (event.GetId())
	{
	case ID_LIST_PICK:
		//mPTRMove = mPlaylist->front();
		mFirstIndex = GetFirstSelected();
		mPTRMove = traverse(mFirstIndex);
		break;
	case ID_LIST_MOVE:
		if (mPTRMove == nullptr)
			return;

		removeTrack(mFirstIndex);
		index = GetFirstSelected();
		if (mFirstIndex <= index)
		{
			offset = 1;
		}
		move(mPTRMove, GetFirstSelected() + offset);
		addTrack(mPTRMove->track, GetFirstSelected() + 1);

		mPTRMove = nullptr;
		mFirstIndex = -1;
		break;
	case ID_LIST_REMOVE:
		index = GetFirstSelected();
		mPlaylist->remove(index);
		removeTrack(index);
		break;
	
	}
}

void PlayListCtrl::OnRightClick(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxMenu mnu;
	mnu.SetClientData(data);
	if(mPTRMove == nullptr)
		mnu.Append(ID_LIST_PICK, "Select");
	else
		mnu.Append(ID_LIST_MOVE, "Move Selected");
	mnu.Append(ID_LIST_REMOVE, "Remove Selected");
	mnu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(PlayListCtrl::OnPopupClick), NULL, this);
	PopupMenu(&mnu);
}
