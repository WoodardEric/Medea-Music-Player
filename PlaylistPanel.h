#ifndef PLAYLISTPANEL_H
#define PLAYLISTPANEL_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "PlayListCtrl.h"

enum PlaylistBox
{
    List = wxID_HIGHEST,
    ListboxPage_Add,
    ListboxPage_AddText,
    ListboxPage_AddSeveral,
    ListboxPage_AddMany,
    ListboxPage_Clear,
    ListboxPage_Change,
    ListboxPage_ChangeText,
    ListboxPage_Delete,
    ListboxPage_DeleteText,
    ListboxPage_DeleteSel,
    ListboxPage_Listbox,
    ListboxPage_EnsureVisible,
    ListboxPage_EnsureVisibleText,
    ListboxPage_ContainerTests,
    ListboxPage_GetTopItem,
    ListboxPage_GetCountPerPage,
    ListboxPage_MoveUp,
    ListboxPage_MoveDown,
};

class PlaylistPanel : public wxPanel
{
public:
	PlaylistPanel(wxWindow *parent);
    PlayListCtrl *mCurrPlaylistCtrl;
private:
	
};

#endif