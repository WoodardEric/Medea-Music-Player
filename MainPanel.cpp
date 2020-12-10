#include "MainPanel.h"
#include "MainFrame.h"

MainPanel::MainPanel(wxPanel *parent, Playlist **list, 
	vector<Track> *vec, vector<Track *> &albumIndex, vector<Track *> &artistIndex)
	: wxPanel(parent, wxID_ANY), mLibrary(*vec), mAlbumIndex(albumIndex), mArtistIndex(artistIndex)
{
	mParent = parent;
	mPTRMove = nullptr;
	mFirstIndex = -1;
	sortByTitle = true;
	sortByArtist = false;
	sortByAlbum = false;
	
	wxBoxSizer *const sizer = new wxBoxSizer(wxHORIZONTAL);
	mPlaylistCtrl = new PlayListCtrl(this, ID_LIST, list);
	
	mLibraryCtrl = new LibraryCtrl(this, ID_LIBRARY);
	mLibraryCtrl->addList(mLibrary);
	sizer->Add(mLibraryCtrl, wxSizerFlags(2).Expand().Border());
	sizer->Add(mPlaylistCtrl, wxSizerFlags(2).Expand().Border());
	SetSizer(sizer);
	
	Bind(wxEVT_LIST_ITEM_ACTIVATED, &MainPanel::OnAtivate, this, ID_LIST);
	Bind(wxEVT_LIST_ITEM_ACTIVATED, &MainPanel::OnLibraryAtivate, this, ID_LIBRARY);
	Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &MainPanel::OnLibraryRightClick, this, ID_LIBRARY);
}
void MainPanel::setPlaylist(Playlist **list)
{
	mPlaylistCtrl->setPlaylist(list);
}
void MainPanel::loadPlayListFromFile(string path)
{
	
}
void MainPanel::clearPlaylist()
{
	mPlaylistCtrl->DeleteAllItems();
	mPlaylistCtrl->clearPlayList();
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
void MainPanel::clearLibraryCtrl()
{
	mLibraryCtrl->ClearAll();
}
void MainPanel::OnAtivate(wxListEvent &event)
{
	MainFrame *frame = (MainFrame *)mParent->GetParent();
	Node *ptr = getFront();
	ptr = mPlaylistCtrl->traverse(mPlaylistCtrl->GetFirstSelected());
	frame->setCurrTrack(ptr);
}

void MainPanel::OnLibraryAtivate(wxListEvent &event)
{	
	sendActivated(mLibraryCtrl->GetFirstSelected());
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


Node *findNode(long i)
{
	return nullptr;
}

void MainPanel::toggleByTitle()
{
	sortByTitle = true;
	sortByAlbum = false;
	sortByArtist = false;
}
void MainPanel::toggleByArtist()
{
	sortByTitle = false;
	sortByAlbum = false;
	sortByArtist = true;
}
void MainPanel::toggleByAlbum()
{
	sortByTitle = false;
	sortByAlbum = true;
	sortByArtist = false;
}
void MainPanel::sendActivated(long index)
{
	if (sortByTitle)
		mPlaylistCtrl->appendTrack(&mLibrary[index]);
	else if (sortByAlbum)
		mPlaylistCtrl->appendTrack(mAlbumIndex[index]);
	else if (sortByArtist)
		mPlaylistCtrl->appendTrack(mArtistIndex[index]);
}

