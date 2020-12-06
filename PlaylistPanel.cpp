#include "PlaylistPanel.h"

PlaylistPanel::PlaylistPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY)
{
	wxBoxSizer *const sizer = new wxBoxSizer(wxVERTICAL);
	mCurrPlaylistCtrl = new PlayListCtrl(this);
	sizer->Add(mCurrPlaylistCtrl, wxSizerFlags(2).Expand().Border());
	SetSizer(sizer);
}