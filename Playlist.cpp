#include "Playlist.h"

Playlist::Playlist(int size)
{
    frameBuffer = new vector<int16_t>(size);
}

void Playlist::readPlayListFile()
{
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
