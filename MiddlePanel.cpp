#include "MiddlePanel.h"

MiddlePanel::MiddlePanel(wxWindow *parent)
	: wxPanel(parent, wxID_ANY)
{
	mList = new wxListView(this);
	mList->SetBackgroundColour(wxColour(179, 198, 253));
}
