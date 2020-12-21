/**********************************************************************
 Medea: A Digital Music Player

 @file  PlaylistPanel.cpp

 @brief:

 holds playlistCtrl, syncs the playlist with the listCtrl, manages the 
 spacing of the playlistCtrl on frame, and catches playlistCtrl events. 

 @author Eric Woodard
 @date   12/11/2020

 **********************************************************************/

#include "PlaylistPanel.h"
#include "MainFrame.h" //used to communicate with parent MainFrame instance 

 /*
 * PlaylistPanel constructor 
 * 
 * @param *parent pointer to parent panel to enable communication with MainFrame.
 */
PlaylistPanel::PlaylistPanel(wxPanel *parent) : wxPanel(parent, wxID_ANY)
{
	mPTRMove = nullptr;
	mFirstIndex = -1;
	mPlaylistCtrl = new PlaylistCtrl(this);
	mParent = parent;
	mSizer = new wxBoxSizer(wxHORIZONTAL);
	mSizer->Add(mPlaylistCtrl, wxSizerFlags(2).Expand().Border());
	SetSizer(mSizer);

	Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &PlaylistPanel::OnRightClick, this, ID_LIST);
	Bind(wxEVT_LIST_ITEM_ACTIVATED, &PlaylistPanel::OnAtivate, this, ID_LIST);
}

/*
* called when mPlaylist item is double clicked or enter is pressed with item selected.
* Sets seleced list item as the currently playing track.
* 
* @param &event activation wxListEvent caught by event handler 
*/
void PlaylistPanel::OnAtivate(wxListEvent &event)
{
	MainFrame *frame = (MainFrame *)mParent->GetParent();
	Node *ptr = mPlaylist.front();
	ptr = mPlaylist.traverse(mPlaylistCtrl->GetFirstSelected());
	frame->setCurrTrack(ptr);
}

/*
* called when mPlaylist item is right clicked.
* Displays menu at item loction where user can
* move or delete the track
*
* @param &event rightclick wxListEvent caught by event handler
*/
void PlaylistPanel::OnRightClick(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxMenu mnu;
	mnu.SetClientData(data);
	if (mPTRMove == nullptr)
		mnu.Append(ID_LIST_PICK, "Select");
	else
		mnu.Append(ID_LIST_MOVE, "Move Selected");
	mnu.Append(ID_LIST_REMOVE, "Remove Selected");
	mnu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(PlaylistPanel::OnPopupClick), NULL, this);
	PopupMenu(&mnu);
}

/*
* Called when mPlaylistCtrl pop up menu item selected.
* Determines the item selected and takes care of the logic
*
* @param &event menu wxCommandEvent caught by event handler. Contains ID for activated menu item
*/
void PlaylistPanel::OnPopupClick(wxCommandEvent &event)
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

		//If node is being moved forward in the list need to account
		//for playlistCtrl being one shorter.
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

/*
* Adds a track to end of both the playlist and playlistCtrl
* 
* @param *track being added to playlist
*/
void PlaylistPanel::appendTrack(Track *track)
{
	mPlaylistCtrl->appendTrack(track);
	mPlaylist.addRear(track);
}

/*
* Deletes a track at a certain index
*
* @param index loction of track in playlist and playlistCtrl
*/
void PlaylistPanel::removeTrack(long index)
{
	mPlaylist.remove(index);
	mPlaylistCtrl->removeTrack(index);
}

/*
* Sets PlaylistCtrl focus to new curretnly playing track
* and removes focus from the previous.
*
* @param currTrack the track that was focused
* @param nextTrack the track to be focused
*/
void PlaylistPanel::focusTrack(const Track *currTrack, const Track *nextTrack)
{
	long index = mPlaylistCtrl->findTrack(currTrack);
	mPlaylistCtrl->Select(index, false);
	index = mPlaylistCtrl->findTrack(nextTrack);
	mPlaylistCtrl->Select(index, true);
}

/*
* Sets PlaylistCtrl focus to new curretnly playing track
*
* @param track the track to be focused
*/
void PlaylistPanel::focusTrack(const Track *track)
{
	long index = mPlaylistCtrl->findTrack(track);
	mPlaylistCtrl->Select(index, true);
}

/*
* Saves current playlist to a csv file by saving track's title, album, and path.
*
* @param path loction playlist will be saved at
*/
void PlaylistPanel::saveCurrPlaylist(string path)
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

/*
* clear mPlaylistCtrl and mPlaylist of all items
*/
void PlaylistPanel::clearPlaylist()
{
	mPlaylistCtrl->DeleteAllItems();
	mPlaylist.clear();
}
