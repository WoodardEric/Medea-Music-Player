#ifndef MAINPANEL_H
#define MAINPANEL_H

#include "IDs.h"
#include "LibraryCtrl.h"
#include "PlayListCtrl.h"

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
    MainPanel(wxPanel *parent, Playlist **list,  
        vector<Track> *vec, vector<Track *> &mAlbumIndex, vector<Track *> &mArtistIndex);
    
    string getListName() const { return mPlaylistCtrl->getName(); }
    //int getListSize() const { return mPlaylist->size(); }
    void setPlaylist(Playlist **list);
   
    void clearLibraryCtrl();

    void OnAtivate(wxListEvent &event);
    void OnLibraryAtivate(wxListEvent &event);
    void OnLibraryRightClick(wxListEvent &event);
    void OnLibraruPopupClick(wxCommandEvent &event);
    Node* findNode(long i);
    Node* findNode(Node* node);
    Node *getFront() const { return mPlaylistCtrl->front(); }
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
    
    vector<Track> &mLibrary;
    vector<Track *> &mAlbumIndex;
    vector<Track *> &mArtistIndex;

    bool mSortByTitle;
    bool mSortByArtist;
    bool mSortByAlbum;
};



#endif