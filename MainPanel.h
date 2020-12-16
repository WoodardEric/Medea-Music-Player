#ifndef MAINPANEL_H
#define MAINPANEL_H

#include "IDs.h"
#include "LibraryCtrl.h"
#include "PlayListCtrl.h"
#include "Playlist.h"

#include <wx/wx.h>
#include <wx/listctrl.h>

#include <fstream>
#include <string>
#include <vector>

using std::string;
using std::ifstream;

class MainPanel : public wxPanel
{
   
public:
    MainPanel(wxPanel *parent, vector<Track> *vec, 
        vector<Track *> &mAlbumIndex, vector<Track *> &mArtistIndex);
    
    const string& getListName() const { return mPlaylist.getName(); }
 
    void appendTrack(Track *track);
    void removeTrack(long index);
    void saveCurrPlaylist(string path);
    void OnPopupClick(wxCommandEvent &event);
    void OnRightClick(wxListEvent &event);

    void OnAtivate(wxListEvent &event);
    void OnLibraryAtivate(wxListEvent &event);
    void OnLibraryRightClick(wxListEvent &event);
    void OnLibraruPopupClick(wxCommandEvent &event);

    void recreateList(short flags);
    void loadPlayListFromFile(string path);
    void clearPlaylist();
    void sendActivated(long index);

    void toggleByTitle();
    void toggleByArtist();
    void toggleByAlbum();
    /*bool isSortByTrack() const { return sortByTrack; }
    bool isSortByArtist() const { return sortByArtist; }
    bool isSortByAlbum() const { return sortByAlbum; }*/
private:
    long mFirstIndex;
    Node *mPTRMove;

    PlayListCtrl *mPlaylistCtrl;
    LibraryCtrl *mLibraryCtrl;
    wxPanel *mParent;

    Playlist mPlaylist;

    vector<Track> &mLibrary;
    vector<Track *> &mAlbumIndex;
    vector<Track *> &mArtistIndex;

    bool mSortByTitle;
    bool mSortByArtist;
    bool mSortByAlbum;
};



#endif