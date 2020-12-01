#pragma once
#include <wx/panel.h>
#include <wx/listctrl.h>
class MiddlePanel : public wxPanel
{
public:
	MiddlePanel(wxWindow *parent);
private:
	wxListView* mList;
};

