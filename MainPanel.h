#ifndef MAINPANEL_H
#define MAINPANEL_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "PlayListCtrl.h"


enum PlaylistBox
{
    ID_LIST = wxID_HIGHEST,
    ID_MOVE,
    ID_PICK,
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
    ListboxPage_GetTopItem,
    ListboxPage_GetCountPerPage,
    ListboxPage_MoveUp,
    ListboxPage_MoveDown,
    ID_PANEL,
};


class MainPanel : public wxPanel
{
public:
    MainPanel(wxPanel *parent, Playlist **list);
    
    string getListName() const { return mPlaylist->getName(); }
    //int getListSize() const { return mPlaylist->size(); }
    void setPlaylist(Playlist **list);
    void OnAtivate(wxListEvent &event);
    void OnRightClick(wxListEvent &event);
    void OnPopupClick(wxCommandEvent &event);
    Node* findNode(long i);
    Node* findNode(Node* node);
    Node *getFront() const { return mPlaylist->front(); }
    void clearPlaylist();

private:
    long mFirstIndex;
    Node *mPTRMove;
    PlayListCtrl *mPlaylistCtrl;
    wxPanel *mParent;
    Playlist *mPlaylist;
};



#endif