#ifndef LIBRARYCTRL_H
#define LIBRARYCTRL_H

#include <wx/listctrl.h>
#include <vector>
#include "Playlist.h"
#include "IDs.h"
using std::vector;

class LibraryCtrl : public wxListView
{
public:
	LibraryCtrl(wxWindow *parent, wxWindowID id);
	void addList(vector<Track> &vec);
	void addList(vector<Track*> &vec);


private:

};

#endif

