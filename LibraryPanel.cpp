/**********************************************************************
 Medea: A Digital Music Player

 @file  LibraryPanel.h

 @brief:

 Holds LibraryCtrl and catches LibraryCtrl events

 @author Eric Woodard
 @date   12/11/2020

 **********************************************************************/
#include "LibraryPanel.h"
#include "MainFrame.h"
 /*
 * LibraryPanel constructor
 *
 * @param *parent of the LibraryPanel
 * @param *vec library of all tracks sorted by title
 * @param &albumIndex sorted index of the library by album
 * @param &albumIndex sorted index of the library by artist
 */
LibraryPanel::LibraryPanel(wxPanel *parent, vector<Track> *vec, 
	vector<Track *> &albumIndex, vector<Track *> &artistIndex)
	: wxPanel(parent, wxID_ANY), 
	mLibrary(*vec), mAlbumIndex(albumIndex), mArtistIndex(artistIndex)
{
	mParent = parent;
	
	mSortByTitle = true;
	mSortByArtist = false;
	mSortByAlbum = false;
	mReversed = false;
	
	mSizer = new wxBoxSizer(wxHORIZONTAL);
	mLibraryCtrl = new LibraryCtrl(this, ID_LIBRARY);
	mLibraryCtrl->addList(mLibrary, false);

	mSizer->Add(mLibraryCtrl, wxSizerFlags(2).Expand().Border());
	SetSizer(mSizer);
	
	Bind(wxEVT_LIST_ITEM_ACTIVATED, &LibraryPanel::OnAtivate, this, ID_LIBRARY);
	Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &LibraryPanel::OnRightClick, this, ID_LIBRARY);
	Bind(wxEVT_LIST_COL_CLICK, &LibraryPanel::OnColClick, this, ID_LIBRARY);
}
/*
 * repopulates LibraryCtrl from sorted library selected by user
 */
void LibraryPanel::recreateList()
{
	mLibraryCtrl->DeleteAllItems();
	mLibraryCtrl->Hide();
	if (mSortByTitle)
	{
		mLibraryCtrl->addList(mLibrary, mReversed);
		toggleByTitle();
	}
	else if (mSortByAlbum)
	{
		mLibraryCtrl->addList(mAlbumIndex, mReversed);
		toggleByAlbum();
	}
	else if (mSortByArtist)
	{
		mLibraryCtrl->addList(mArtistIndex, mReversed);
		toggleByArtist();
	}
	
	mLibraryCtrl->Show();
}
/*
 * Called when mLibraryCtrl item is ativated by double click or enter.
 * Selects which item(s) to be send to the playlist.
 * 
 * @param &event wxListEvent caught by event handler
 */
void LibraryPanel::OnAtivate(wxListEvent &event)
{	
	sendActivated(mLibraryCtrl->GetFirstSelected());
}
/*
 * Called when mLibraryCtrl item is right clicked
 * Displays a popup menu at item location
 *
 * @param &event wxListEvent caught by event handler
 */
void LibraryPanel::OnRightClick(wxListEvent &event)
{
	void *data = reinterpret_cast<void *>(event.GetItem().GetData());
	wxMenu mnu;
	mnu.SetClientData(data);
	mnu.Append(ID_QUEUE, "Queue to play list");
	mnu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(LibraryPanel::OnPopupClick), NULL, this);
	PopupMenu(&mnu);
}
/*
 * Called when popup menu item is selected
 * Handles which popup menu item is selected
 *
 * @param &event menu wxCommandEvent caught by event handler. Gets ID of menu item slected
 */
void LibraryPanel::OnPopupClick(wxCommandEvent &event)
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
/*
 * Called when colum header is left clicked
 * resorts the library based on user selection
 *
 * param &event wxListEvent caught by event handler. Determines which colum was clicked
 */
void LibraryPanel::OnColClick(wxListEvent &event)
{
	if (event.GetColumn() == 0)
	{
		if (mSortByTitle)
		{
			mReversed = !mReversed;
		}
		else
		{
			mReversed = false;
		}

		toggleByTitle();
		recreateList();
		
	}
	else if (event.GetColumn() == 2)
	{
		if (mSortByAlbum)
		{
			mReversed = !mReversed;
		}
		else
		{
			mReversed = false;
		}
		toggleByAlbum();
		recreateList();
	}
	else if (event.GetColumn() == 3)
	{
		if (mSortByArtist)
		{
			mReversed = !mReversed;
		}
		else
		{
			mReversed = false;
		}
		toggleByArtist();
		recreateList();
	}
	else
		event.Skip();
}
/*
* Toggles sorting state to sort by title while setting other states to false.
*/
void LibraryPanel::toggleByTitle()
{
	mSortByTitle = true;
	mSortByAlbum = false;
	mSortByArtist = false;
}
/*
* Toggles sorting state to sort by artist while setting other states to false.
*/
void LibraryPanel::toggleByArtist()
{
	mSortByTitle = false;
	mSortByAlbum = false;
	mSortByArtist = true;
}
/*
* Toggles sorting state to sort by album while setting other states to false.
*/
void LibraryPanel::toggleByAlbum()
{
	mSortByTitle = false;
	mSortByAlbum = true;
	mSortByArtist = false;
}
/*
* sends selected item(s) to playlist. If playlist is empty then populates 
* the playlist based on current sorting selection.
* 
* @param index of the first item from the LibraryCtrl being sent
*/
void LibraryPanel::sendActivated(long index)
{
	MainFrame *frame = (MainFrame *)mParent->GetParent();
	//If playlist empty populates playlist based on sorting method
	if (frame->getPlaylistPanel()->getPlaylistSize() == 0)
	{
		if (mSortByTitle)
		{
			while (index < index + 20 && index < mLibrary.size())
			{
				frame->getPlaylistPanel()->appendTrack(&mLibrary[index]);
				++index;
			}
		}
		else if (mSortByAlbum)
		{
			Track *track = mAlbumIndex[index];
			string album = track->album;
			int i = index;

			while (track->album == album)//sends all tracks after the activated track from an album
			{
				frame->getPlaylistPanel()->appendTrack(mAlbumIndex[i]);
				++i;
				track = mAlbumIndex[i];
			}
		}
		else if (mSortByArtist)
		{
			Track *track = mArtistIndex[index];
			string artist = track->artist;
			int i = index;

			while (track->artist == artist)//sends all tracks after the activated track from an artist
			{
				frame->getPlaylistPanel()->appendTrack(mArtistIndex[i]);
				++i;
				track = mArtistIndex[i];
			}
		}
	}
	else //If playlist not empty append selected item(s) to playlist
	{
		if (mSortByTitle)
		{
			if (mReversed)
				frame->getPlaylistPanel()->appendTrack(&mLibrary[(mLibrary.size() - 1) - index]);

			else
				frame->getPlaylistPanel()->appendTrack(&mLibrary[index]);
		}
		else if (mSortByAlbum)
		{
			if (mReversed)
				frame->getPlaylistPanel()->appendTrack(mArtistIndex[(mArtistIndex.size() - 1) - index]);
			else
				frame->getPlaylistPanel()->appendTrack(mAlbumIndex[index]);
		}
		else if (mSortByArtist)
		{
			if (mReversed)
				frame->getPlaylistPanel()->appendTrack(mArtistIndex[(mArtistIndex.size() - 1) - index]);
			else
				frame->getPlaylistPanel()->appendTrack(mArtistIndex[index]);
		}
	}
}

