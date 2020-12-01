#include "PlaylistPanel.h"


PlaylistPanel::PlaylistPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY)
{
	//this->setStyle
	mList = new wxListView(this, PlaylistBox::List, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_HRULES);

	mList->AppendColumn(wxString("Song"),wxLIST_FORMAT_LEFT, -1);
	mList->AppendColumn(wxString("Time"), wxLIST_FORMAT_LEFT, -1);
	mList->InsertItem(0, wxString("Fly Me To The Moon"));
	mList->SetColumnWidth(0, wxLIST_AUTOSIZE);
	mList->InsertItem(1, wxString("Green Onions"));
}