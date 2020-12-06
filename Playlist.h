#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
#include <fstream>

using std::ifstream;
using std::vector;
using std::string;

struct Track
{
	string song;
	string album;
	string artist;
	string genre;
	short rating;
	string path;
	int timesPlayed;
};

struct Node
{
	Node(Track track, Node *next = nullptr, Node *prev = nullptr)
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
	Track track;
	Node *next;
	Node *prev;
};

class Playlist
{

	

public:

	Playlist(int size = 0);
	~Playlist();
	
	Node* front() { return mHead; }
	void readPlayListFile();
	void writePlayListFile();

	void addFront(Track track);
	void addRear(Track track);

	void insert(Node *node, Track track);
	void remove(string song);
	void moveTrack();

	void play(string song);

	string toString();

private:
	int mSize;
	Node *mHead;
	Node *mTail;
	
};

#endif
