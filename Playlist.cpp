/**********************************************************************
 Medea: A Digital Music Player

 @file  Playlist.cpp

 @brief:

 Manages the playlist which is a doubly linked list and the nodes hold
 a pointer to a track from the master playlist vector.

 @author Eric Woodard
 @date   12/11/2020

 TODO: figure out where to place Track struct in project
 **********************************************************************/
#include "Playlist.h"

 /*
 * Default Playlist constructor
 */
Playlist::Playlist()
{
    mHead = nullptr;
    mTail = nullptr;
    mSize = 0;
    mName = "5TrackWonder";
}

/*
 * Default Playlist destructor
 */
Playlist::~Playlist()
{
    clear();
}

/*
 * Adds track to the front of the playList
 * 
 * @param *track to be added at the front of the playlist
 */
void Playlist::addFront(Track *track)
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
/*
 * Adds track to the rear of the playList
 *
 * @param *track to be added at the rear of the playlist
 */
void Playlist::addRear(Track *track)
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
/*
 * deletes every node in the playlist and sets mSize to 0
 *
 */
void Playlist::clear()
{
    while (mHead != nullptr)
    {
        Node *ptr = mHead;
        mHead = mHead->next;
        delete ptr;
        ptr = mHead;
    }
    mTail = nullptr;
    mSize = 0;
}
/*
 * moves a track node to a different location in the playlist
 *
 * @param *node being moved
 * @param index location where the node is being moved.
 */
void Playlist::move(Node *node, long index)
{
    Node *ptr = traverse(index);
   
    if (node == mHead)
    {
        mHead = mHead->next;
        mHead->prev = nullptr;
    }
    if (ptr->next != nullptr)
    {
        ptr->next->prev = node;
        if (ptr->next->next == node)
        {
            ptr->next->next = node->next;
        }
    }
   
    if (node->next == ptr)
    {
        node->prev->next = ptr;
        ptr->prev = node->prev;
        node->next = ptr->next;
        ptr->next = node;
        node->prev = ptr;
    }
    else
    {
        if(node->next != nullptr)
            node->next->prev = node->prev;
        if(node->prev != nullptr)
            node->prev->next = node->next;

        node->next = ptr->next;
        ptr->next = node;
        node->prev = ptr;
    }
    
    if (node->next == nullptr)
    {
        mTail = node;
        mTail->next = nullptr;
    }
}
/*
 * removes a track node from a specific location in the playlist
 *
 * @param index location of the node being deleted.
 */
void Playlist::remove(long index)
{
    Node *ptr = traverse(index);
    if (ptr == mHead)
    {
        mHead = ptr->next;
        if(ptr->next != nullptr)
            mHead->prev = nullptr;
        else
        {
            mTail = mHead = nullptr;
            mSize = 0;
        }
    }
    else if(ptr == mTail)
    {
        mTail = ptr->prev;
        mTail->next = nullptr;
    }
    else
    {
        ptr->next->prev = ptr->prev;
        ptr->prev->next = ptr->next;
    }
    delete ptr;
}

/*
 * traverses the playlist to an index 
 *
 * @param index of the location being sought.
 * @return a pointer to the node at the index.
 */
Node* Playlist::traverse(const long index)
{
    Node *node = mHead;
    for (int i = 0; i < index; ++i)
    {
        node = node->next;
    }
    return node;
}
