/**********************************************************************
 Medea: A Digital Music Player

 @file  LibraryPanel.h

 @brief:

 Holds LibraryCtrl and catches LibraryCtrl events

 @author Eric Woodard
 @date   12/11/2020

 TODO: 
 Allow multiple track to be appended to a populated playlist
 Allow user to edit track info
 **********************************************************************/
#ifndef MAINPANEL_H
#define MAINPANEL_H

#include "IDs.h"
#include "LibraryCtrl.h"
#include "PlayListCtrl.h"
#include "Playlist.h"

#include "PlaylistPanel.h"

#include <wx/wx.h>
#include <wx/listctrl.h>

//#include <fstream>
#include <string>
#include <vector>

using std::string;
//using std::ifstream;

class LibraryPanel : public wxPanel
{
public:
    LibraryPanel(wxPanel *parent, vector<Track> *vec, 
        vector<Track *> &mAlbumIndex, vector<Track *> &mArtistIndex);
    
    void OnAtivate(wxListEvent &event);
    void OnRightClick(wxListEvent &event);
    void OnPopupClick(wxCommandEvent &event);
    void OnColClick(wxListEvent &event);

    void toggleByTitle();
    void toggleByArtist();
    void toggleByAlbum();

    void recreateList();
    void sendActivated(long index);

private:
    LibraryCtrl *mLibraryCtrl;
    wxPanel *mParent;
  
    wxBoxSizer *mSizer;
    vector<Track> &mLibrary;
    vector<Track *> &mAlbumIndex;
    vector<Track *> &mArtistIndex;

    bool mSortByTitle; //library sorted by track title 
    bool mSortByAlbum; //library sorted by track album
    bool mSortByArtist; //library sorted by track artist
    bool mReversed; //library sorted in reverse
};



#endif