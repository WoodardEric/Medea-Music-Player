#ifndef IDS_H
#define IDS_H

#include <wx/wx.h> 

enum MusicPlayerIDs
{
    // Menu event IDs
    ID_PLAY = wxID_HIGHEST,
    ID_PAUSE,
    ID_NEXT,
    ID_PREV,
    ID_LOOP,
    ID_LOOPALL,
    ID_STOP,
    ID_SAVE,
    ID_LOAD,
    ID_CLEAR,
    ID_TITLE,
    ID_ARTIST,
    ID_ALBUM,
    ID_SCAN,
    ID_DIR,

    ID_VOL_SLIDER,
    ID_TIME_SLIDER,

    ID_SELECT,
    ID_LIST_REMOVE,
    ID_LIST,
    ID_LIST_MOVE,
    ID_LIST_PICK,
    ID_LIBRARY,
    ID_MOVE,
    ID_PICK,
    ID_QUEUE,
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
#endif

