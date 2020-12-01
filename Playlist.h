#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
using std::vector;
using std::string;



class Playlist
{

	struct Track
	{
		string song;
		string album;
		string artist;
		string genre;
		short rating;
		string path;
	};

	struct Node
	{
		Node(Track track, Node *next = nullptr, Node *prev = nullptr) 
		{
			this->track = track;
			this->next = next;
			this->prev = prev;
		}
		Track track;
		Node *next;
		Node *prev;
	};

public:

	Playlist(int size);
	~Playlist();
	
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
	vector<int16_t> *frameBuffer;
};

#endif
