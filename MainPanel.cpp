#include "MainPanel.h"
#include "MainFrame.h"

MainPanel::MainPanel(wxPanel *parent, vector<Track> *vec, 
	vector<Track *> &albumIndex, vector<Track *> &artistIndex)
	: wxPanel(parent, wxID_ANY), mLibrary(*vec), mAlbumIndex(albumIndex), mArtistIndex(artistIndex)
{
	mParent = parent;
	mPTRMove = nullptr;
	mFirstIndex = -1;
	mSortByTitle = true;
	mSortByArtist = false;
	mSortByAlbum = false;
	
	wxBoxSizer *const sizer = new wxBoxSizer(wxHORIZONTAL);
	mPlaylistCtrl = new PlayListCtrl(this, ID_LIST);
	
	mLibraryCtrl = new LibraryCtrl(this, ID_LIBRARY);
	mLibraryCtrl->addList(mLibrary);
	sizer->Add(mLibraryCtrl, wxSizerFlags(2).Expand().Border());
	sizer->Add(mPlaylistCtrl, wxSizerFlags(2).Expand().Border());
	SetSizer(sizer);
	
	Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &MainPanel::OnRightClick, this, ID_LIST);
	Bind(wxEVT_LIST_ITEM_ACTIVATED, &MainPanel::OnAtivate, this, ID_LIST);
	Bind(wxEVT_LIST_ITEM_ACTIVATED, &MainPanel::OnLibraryAtivate, this, ID_LIBRARY);
	Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &MainPanel::OnLibraryRightClick, this, ID_LIBRARY);
}

void MainPanel::loadPlayListFromFile(string path)
{
	
}
void MainPanel::clearPlaylist()
{
	mPlaylistCtrl->DeleteAllItems();
	mPlaylist.clear();
}
void MainPanel::recreateList(short flags)
{
	mLibraryCtrl->DeleteAllItems();
	mLibraryCtrl->Hide();
	if (flags == 00)
	{
		mLibraryCtrl->addList(mLibrary);
		toggleByArtist();
	}
	else if (flags == 10)
	{
		mLibraryCtrl->addList(mAlbumIndex);
		toggleByAlbum();
	}
	else if (flags == 20)
	{
		mLibraryCtrl->addList(mArtistIndex);
		toggleByArtist();
	}
	/*else if (flags == 01)
	{

	}
	else if (flags == 11)
	{

	}
	else if (flags == 21)
	{

	}*/
	mLibraryCtrl->Show();
}


void MainPanel::OnAtivate(wxListEvent &event)
{
	MainFrame *frame = (MainFrame *)mParent->GetParent();
	Node *ptr = mPlaylist.front();
	ptr = mPlaylist.traverse(mPlaylistCtrl->GetFirstSelected());
	frame->setCurrTrack(ptr);
}

void MainPanel::OnLibraryAtivate(wxListEvent &event)
{	
	sendActivated(mLibraryCtrl->GetFirstSelected());
}
void MainPanel::OnPopupClick(wxCommandEvent &event)
{
	int offset = 0;
	int index = -1;
	switch (event.GetId())
	{
	case ID_LIST_PICK:
		mFirstIndex = mPlaylistCtrl->GetFirstSelected();
		mPTRMove = mPlaylist.traverse(mFirstIndex);
		break;
	case ID_LIST_MOVE:
		if (mPTRMove == nullptr)
			return;

		mPlaylistCtrl->removeTrack(mFirstIndex);
		index = mPlaylistCtrl->GetFirstSelected();
		if (mFirstIndex <= index)
		{
			offset = 1;
		}
		mPlaylist.move(mPTRMove, mPlaylistCtrl->GetFirstSelected() + offset);
		mPlaylistCtrl->addTrack(mPTRMove->track, mPlaylistCtrl->GetFirstSelected() + 1);

		mPTRMove = nullptr;
		mFirstIndex = -1;
		break;
	case ID_LIST_REMOVE:
		index = mPlaylistCtrl->GetFirstSelected();
		removeTrack(index);
		break;

	}
}

void MainPanel::OnRightClick(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxMenu mnu;
	mnu.SetClientData(data);
	if (mPTRMove == nullptr)
		mnu.Append(ID_LIST_PICK, "Select");
	else
		mnu.Append(ID_LIST_MOVE, "Move Selected");
	mnu.Append(ID_LIST_REMOVE, "Remove Selected");
	mnu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainPanel::OnPopupClick), NULL, this);
	PopupMenu(&mnu);
}

void MainPanel::OnLibraryRightClick(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxMenu mnu;
	mnu.SetClientData(data);
	mnu.Append(ID_QUEUE, "Queue to play list");
	mnu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainPanel::OnLibraruPopupClick), NULL, this);
	PopupMenu(&mnu);
}
void MainPanel::OnLibraruPopupClick(wxCommandEvent &event)
{
	switch (event.GetId())
	{
	case ID_QUEUE:
		sendActivated(mLibraryCtrl->GetFirstSelected());
		break;
	default:
		event.Skip();
		break;
	}
}

void MainPanel::toggleByTitle()
{
	mSortByTitle = true;
	mSortByAlbum = false;
	mSortByArtist = false;
}

void MainPanel::toggleByArtist()
{
	mSortByTitle = false;
	mSortByAlbum = false;
	mSortByArtist = true;
}

void MainPanel::toggleByAlbum()
{
	mSortByTitle = false;
	mSortByAlbum = true;
	mSortByArtist = false;
}

void MainPanel::sendActivated(long index)
{
	if (sortByTitle)
	{
		appendTrack(&mLibrary[index]);
	}
	else if (sortByAlbum)
	{
		appendTrack(mAlbumIndex[index]);
	}
	else if (sortByArtist)
	{
		appendTrack(mArtistIndex[index]);
	}
}

void MainPanel::appendTrack(Track *track)
{
	mPlaylistCtrl->appendTrack(track);
	mPlaylist.addRear(track);
}

void MainPanel::removeTrack(long index)
{
	mPlaylist.remove(index);
	mPlaylistCtrl->removeTrack(index);
}

void MainPanel::saveCurrPlaylist(string path)
{
	Node *ptr = mPlaylist.front();
	fstream outFile(path + mPlaylist.getName(), ios_base::out);
	if (!outFile)
	{
		wxMessageBox(wxT("Could not load file." + mPlaylist.getName()));
		return;
	}

	while (ptr->next != nullptr)
	{
		outFile << ptr->track->title << ',' << ptr->track->album << ','
			<< ptr->track->path << '\n';
		ptr = ptr->next;
	}

	outFile << ptr->track->title << ',' << ptr->track->album << ','
		<< ',' << ptr->track->path;
}