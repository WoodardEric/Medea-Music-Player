#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "MusicFile.h"

using std::fstream;
using std::string;
using std::ios;
using std::ios_base;

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
	//~Playlist();
	
	Node* front() const  { return mHead; } 
	Node* rear() const { return mTail; }	
	int size() { return mSize; }
	const string& getName() const { return mName; }

	void readPlayListFile();
	void writePlayListFile();

	void addFront(Track *track);
	void addRear(Track *track);

	void clear();

	void insert(Node *node, Track *track);
	void move(Node *node, long index);
	Node* traverse(long index);
	void remove(long index);
	void moveTrack();

	string toString();

private:
	int mSize;
	Node *mHead;
	Node *mTail;
	string mName;
	
};

#endif
