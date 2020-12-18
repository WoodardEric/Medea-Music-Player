/**********************************************************************
 Medea: A Digital Music Player

 @file  index.h

 @brief:

sorts and seraches the music track vecotrs.

 @author Eric Woodard
 @date   12/11/2020

 //TODO: 
 won't let me change the name to Index.h
 Convert sorting to quicksort
 **********************************************************************/
#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <vector>
#include "Playlist.h"

using std::vector;
using std::string;

void attachIndexToVector(vector<Track*> &index, vector<Track> &vec);

void sortByTitle(vector<Track> &index);

void sortByAlbum(vector<Track*> &index);
void sortByArtist(vector<Track*> &index);

int searchByTitle(vector<Track> &index, string title);
int searchByAlbum(vector<Track*> &index, string album);
int searchByArtist(vector<Track*> &index, string artist);

#endif
