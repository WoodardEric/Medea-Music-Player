#include "MainPanel.h"
#include "MainFrame.h"

MainPanel::MainPanel(wxPanel *parent, Playlist **list) : wxPanel(parent, wxID_ANY)
{
	mParent = parent;
	mPlaylist = *list;
	mPTRMove = nullptr;
	mFirstIndex = -1;
	wxBoxSizer *const sizer = new wxBoxSizer(wxVERTICAL);
	mPlaylistCtrl = new PlayListCtrl(this, ID_LIST);
	mPlaylistCtrl->addList(*mPlaylist);
	sizer->Add(mPlaylistCtrl, wxSizerFlags(2).Expand().Border());
	SetSizer(sizer);
	Bind(wxEVT_LIST_ITEM_ACTIVATED, &MainPanel::OnAtivate, this, ID_LIST);
	Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &MainPanel::OnRightClick, this, ID_LIST);
}
void MainPanel::setPlaylist(Playlist **list)
{
	mPlaylist = *list;
}

void MainPanel::OnAtivate(wxListEvent &event)
{
	MainFrame *frame = (MainFrame *)mParent->GetParent();
	Node *ptr = mPlaylist->front();
	ptr = mPlaylist->traverse(mPlaylistCtrl->GetFirstSelected());
	frame->setCurrTrack(ptr);
}

void MainPanel::OnRightClick(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxMenu mnu;
	mnu.SetClientData(data);
	mnu.Append(ID_PICK, "Select");
	mnu.Append(ID_MOVE, "Move Selected");
	mnu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainPanel::OnPopupClick), NULL, this);
	PopupMenu(&mnu);
}

void MainPanel::OnPopupClick(wxCommandEvent &event)
{
	
	switch (event.GetId())
	{
	case ID_PICK:
		//mPTRMove = mPlaylist->front();
		mFirstIndex = mPlaylistCtrl->GetFirstSelected();
		mPTRMove = mPlaylist->traverse(mFirstIndex);
		break;
	case ID_MOVE:
		if (mPTRMove == nullptr)
			return;

		mPlaylistCtrl->removeTrack(mFirstIndex);
		int offset = 0;
		int index = mPlaylistCtrl->GetFirstSelected();
		if (mFirstIndex <= index)
		{
			offset = 1;
		}
		mPlaylist->insert(mPTRMove, mPlaylistCtrl->GetFirstSelected() + offset);
		mPlaylistCtrl->addTrack(mPTRMove, mPlaylistCtrl->GetFirstSelected() + 1);

		mPTRMove = nullptr;
		mFirstIndex = -1;
			break;
	}
}

void MainPanel::clearPlaylist()
{
	mPlaylist->clear();
}

Node *findNode(long i)
{
	return nullptr;
}

