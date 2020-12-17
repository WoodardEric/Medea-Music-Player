/**********************************************************************
 Medea: A Digital Music Player

 @file  LibraryCtrl.cpp

 @brief:

 Populates and displays music library to a list on the screen

 @author Eric Woodard
 @date   12/11/2020

 **********************************************************************/
#include "LibraryCtrl.h"
/*
* LibraryCtrl constructor
* @param *parent of LibraryCtrl
* @param id unique identifier of LibraryCtrl
*/
LibraryCtrl::LibraryCtrl(wxWindow *parent, wxWindowID id)
	: wxListView(parent, id, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_HRULES)
{
	//set up columns for LibraryCtrl
	wxListItem col0;
	col0.SetId(0);
	col0.SetText(_("Title"));
	col0.SetWidth(150);
	InsertColumn(0, col0);
		       
	wxListItem col1;
	col1.SetId(1);
	col1.SetText(_("#"));
	col1.SetWidth(30);
	InsertColumn(1, col1);
	   
	wxListItem col2;
	col2.SetId(2);
	col2.SetText(_("Album"));
	col2.SetWidth(100);
	InsertColumn(2, col2);

	wxListItem col3;
	col3.SetId(3);
	col3.SetText(_("Artist"));
	col3.SetWidth(100);
	InsertColumn(3, col3);

	wxListItem col4;
	col4.SetId(4);
	col4.SetText(_("Genre"));
	col4.SetWidth(100);
	InsertColumn(4, col4);

	/*wxListItem col4;
	col4.SetId(4);
	col4.SetText(_("Time"));
	col4.SetWidth(50);
	InsertColumn(4, col4);*/

}

/*
* adds the library to the LibraryCtrl and displays all of the track
* 
* @param &vec library to be inserted into the LibraryCtrl
*/
void LibraryCtrl::addList(const vector<Track> &vec, const bool reversed)
{
	if (!reversed)
	{
		for (size_t i = 0; i < vec.size(); ++i)
		{
			wxString num = wxString::Format(wxT("%i"), vec[i].trackNumber);
			long itemIndex = InsertItem(GetItemCount(), vec[i].title);
			SetItem(itemIndex, 1, num);
			SetItem(itemIndex, 2, vec[i].album);
			SetItem(itemIndex, 3, vec[i].artist);
			SetItem(itemIndex, 4, vec[i].genre);
			//SetItem(itemIndex, 4, vec[i].length);
		}
	}
	else
	{
		for (size_t i = vec.size() - 1; i > 0; --i)
		{
			wxString num = wxString::Format(wxT("%i"), vec[i].trackNumber);
			long itemIndex = InsertItem(GetItemCount(), vec[i].title);
			SetItem(itemIndex, 1, num);
			SetItem(itemIndex, 2, vec[i].album);
			SetItem(itemIndex, 3, vec[i].artist);
			SetItem(itemIndex, 4, vec[i].genre);
			//SetItem(itemIndex, 4, vec[i].length);
		}
	}
}

/*
* adds the indexed library to the LibraryCtrl and displays all of the track
*
* @param &vec indexed library to be inserted into the LibraryCtrl
*/
void LibraryCtrl::addList(const vector<Track*> &vec, const bool reversed)
{
	if (!reversed)
	{
		for (size_t i = 0; i < vec.size(); ++i)
		{
			wxString num = wxString::Format(wxT("%i"), vec[i]->trackNumber);
			long itemIndex = InsertItem(GetItemCount(), vec[i]->title);
			SetItem(itemIndex, 1, num);
			SetItem(itemIndex, 2, vec[i]->album);
			SetItem(itemIndex, 3, vec[i]->artist);
			SetItem(itemIndex, 4, vec[i]->genre);
			//SetItem(itemIndex, 4, vec[i]->length);
		}
	}
	else
	{
		for (size_t i = vec.size() - 1; i > 0; --i)
		{
			wxString num = wxString::Format(wxT("%i"), vec[i]->trackNumber);
			long itemIndex = InsertItem(GetItemCount(), vec[i]->title);
			SetItem(itemIndex, 1, num);
			SetItem(itemIndex, 2, vec[i]->album);
			SetItem(itemIndex, 3, vec[i]->artist);
			SetItem(itemIndex, 4, vec[i]->genre);
			//SetItem(itemIndex, 4, vec[i]->length);
		}
	}
}

