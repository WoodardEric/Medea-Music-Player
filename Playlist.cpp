#include "Playlist.h"


Playlist::Playlist(int size)
{
    mHead = nullptr;
    mTail = nullptr;
    readPlayListFile();
}

void Playlist::readPlayListFile()
{
    std::ifstream inFile("data/playList.csv");

    if (!inFile)
    {
      
    }

    while (!inFile.eof())
    {
        char del;
        Track rec;
        getline(inFile, rec.artist, ',');
        getline(inFile, rec.album, ',');
        getline(inFile, rec.song, ',');
        getline(inFile, rec.genre, ',');
        inFile >> rec.timesPlayed;
        inFile >> del;
        inFile >> rec.rating;
        inFile.get(del);

        addRear(rec);
    }
    inFile.close();
}

void Playlist::writePlayListFile()
{
}

void Playlist::addFront(Track track)
{
    if (mHead == nullptr)
    {
        mTail = mHead = new Node(track);
    }
    else
    {
        mHead = new Node(track, mHead);
        mHead->next->prev = mHead;
    }

    ++mSize;
}

void Playlist::addRear(Track track)
{
    if (mTail == nullptr)
    {
        mHead = mTail = new Node(track);
    }
    else
    {
        mTail = new Node(track, nullptr, mTail);
        mTail->prev->next = mTail;
    }

    ++mSize;
}

void Playlist::insert(Node* node, Track track)
{
    Node* newNode = new Node(track, node->next, node);
    node->next = newNode;
    newNode->next->prev = newNode;
}

void Playlist::remove(string song)
{

}

void Playlist::moveTrack()
{
}

void Playlist::play(string song)
{
}

string Playlist::toString()
{
    return string();
}
