/**********************************************************************
 Medea: A Digital Music Player

 @file  Playlist.h

 @brief:

 Manages the playlist which is a doubly linked list and the nodes hold 
 a pointer to a track from the master playlist vector.

 @author Eric Woodard
 @date   12/11/2020

 TODO: figure out where to place struct Track in project
 **********************************************************************/
#ifndef PLAYLIST_H
#define PLAYLIST_H

//ignores compile error about std function deprecation in wxWidgets' wxcrt.h
#pragma warning(disable : 4996) 
#include "MusicFile.h"

struct Track
{
	string title = "Unkown";
	string album = "Unkown";
	string artist = "Unkown";
	short year = 0000;
	string genre = "Unkown";
	short trackNumber = 0;

	int length = 0;
	short rating = 0;
	int timesPlayed = 0;
	string path = "";
};

struct Node
{
	Node(Track *track, Node *next = nullptr, Node *prev = nullptr)
	{
		this->track = track;
		this->next = next;
		this->prev = prev;
	}
	~Node()
	{
		next = nullptr;
		prev = nullptr;
	}
	Track *track;
	Node *next;
	Node *prev;
};

class Playlist
{
public:

	Playlist();
	~Playlist();
	
	Node* front() const  { return mHead; } 
	Node* rear() const { return mTail; }	
	int size() const { return mSize; }
	const string& getName() const { return mName; }

	void addFront(Track *track);
	void addRear(Track *track);
	void clear();
	
	void move(Node *node, long index);
	void remove(long index);
	Node *traverse(const long index);

private:
	int mSize;
	Node *mHead;
	Node *mTail;
	string mName; //name of playlist
};

#endif
