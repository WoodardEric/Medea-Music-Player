#include "LibraryCtrl.h"

LibraryCtrl::LibraryCtrl(wxWindow *parent, wxWindowID id)
	: wxListView(parent, id, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_HRULES)
{
	
	// Add first column        
	wxListItem col0;
	col0.SetId(0);
	col0.SetText(_("Title"));
	col0.SetWidth(150);
	InsertColumn(0, col0);
	
	// Add first column        
	wxListItem col1;
	col1.SetId(1);
	col1.SetText(_("#"));
	col1.SetWidth(30);
	InsertColumn(1, col1);

	// Add first column        
	wxListItem col2;
	col2.SetId(2);
	col2.SetText(_("Album"));
	col2.SetWidth(100);
	InsertColumn(2, col2);

	// Add second column 
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

void LibraryCtrl::addList(vector<Track> &vec)
{
	for(size_t i = 0; i < vec.size(); ++i)
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

void LibraryCtrl::addList(vector<Track*> &vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		wxString num = wxString::Format(wxT("%i"), vec[i]->trackNumber);
		long itemIndex = InsertItem(GetItemCount(), vec[i]->title); 
		SetItem(itemIndex, 1, num);
		SetItem(itemIndex, 2, vec[i]->album); 
		SetItem(itemIndex, 3, vec[i]->artist); 
		SetItem(itemIndex, 4, vec[i]->genre);
		//SetItem(itemIndex, 4, vec[i].length);
	}
}

