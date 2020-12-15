#include "Playlist.h"


Playlist::Playlist()
{
    mHead = nullptr;
    mTail = nullptr;
    mSize = 0;
    mName = "5TrackWonder";
    //readPlayListFile();
}

//void Playlist::readPlayListFile()
//{
//    fstream inFile("data/playList.csv", ios_base::in);
//
//    if (!inFile)
//    {
//      
//    }
//
//    while (!inFile.eof())
//    {
//        char del;
//        Track rec;
//        getline(inFile, rec.artist, ',');
//        getline(inFile, rec.album, ',');
//        getline(inFile, rec.title, ',');
//        getline(inFile, rec.genre, ',');
//        inFile >> rec.timesPlayed;
//        inFile >> del;
//        inFile >> rec.rating;
//        inFile.get(del);
//
//        addRear(rec);
//    }
//    inFile.close();
//}

void Playlist::writePlayListFile()
{
}

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
//void Playlist::insert(Node* node, Track *track)
//{
//    Node* newNode = new Node(track, node->next, node);
//    node->next = newNode;
//    newNode->next->prev = newNode;
//}
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


Node* Playlist::traverse(long index)
{
    Node *node = mHead;
    for (int i = 0; i < index; ++i)
    {
        node = node->next;
    }
    return node;
}

string Playlist::toString()
{
    return string();
}


