/**
 * @file   index.cpp
 * @brief  contains function definitions for sorting and searching indexes
 *
 * @author Eric Woodard
 * @date   09/09/2020
 * 
 * TODO: update sorting to quick sort
 */
#include "index.h"
 /**
  * attaches the vector of pointers to the vector of students
  *
  * @param index vector of pointers indexed to students vector.
  * @param vec vector of students
  */
void attachIndexToVector(vector<Track *> &index, vector<Track> &vec)
{
    for (int i = 0; i < vec.size(); ++i)
        index.push_back(&vec[i]);
}
/**
 * uses selction sort to sort pointers by last name in alphabetical order
 *
 * @param index vector of pointers indexed to students vector.
 */
void sortByTitle(vector<Track> &index)
{
    for (int startscan = 0; startscan < index.size() - 1; ++startscan)
    {
        int minIndex = startscan;
        Track minValue = index[startscan];

        for (int i = startscan + 1; i < index.size(); ++i)
        {
            if (index[i].title < minValue.title)
            {
                minValue = index[i];
                minIndex = i;
            }
        }
        index[minIndex] = index[startscan];
        index[startscan] = minValue;

    }
}
/**
 * uses selction sort to sort pointers by ssn in ascending order
 *
 * @param index vector of pointers indexed to students vector.
 */
void sortByAlbum(vector<Track *> &index)
{
    for (int startscan = 0; startscan < index.size() - 1; ++startscan)
    {
        int minIndex = startscan;
        Track *minValue = index[startscan];

        for (int i = startscan + 1; i < index.size(); ++i)
        {
            if (index[i]->album < minValue->album)
            {
                minValue = index[i];
                minIndex = i;
            }
            else if (index[i]->album == minValue->album && 
                index[i]->trackNumber < minValue->trackNumber)
            {
                minValue = index[i];
                minIndex = i;
            }
        }
        index[minIndex] = index[startscan];
        index[startscan] = minValue;

    }
}

/**
 * uses selction sort to sort pointers by first name in alphabetical order
 * @param index vector of pointers indexed to students vector.
 */
void sortByArtist(vector<Track *> &index)
{
    for (int startscan = 0; startscan < index.size() - 1; ++startscan)
    {
        int minIndex = startscan;
        Track *minValue = index[startscan];

        for (int i = startscan + 1; i < index.size(); ++i)
        {
            if (index[i]->artist < minValue->artist)
            {
                minValue = index[i];
                minIndex = i;
            }
            else if (index[i]->artist == minValue->artist && index[i]->album < minValue->album)
            {
                minValue = index[i];
                minIndex = i;
            }
            else if (index[i]->artist == minValue->artist
                && index[i]->album == minValue->album
                && index[i]->trackNumber < minValue->trackNumber)
            {
                minValue = index[i];
                minIndex = i;
            }

        }
        index[minIndex] = index[startscan];
        index[startscan] = minValue;
    }
}
/**
 * uses binary search to find index in the vector of last name being searched for
 *
 * TODO: Deal with repeat titles
 * 
 * @param index vector of pointers indexed to students vector.
 * @param name name being searched for
 */
int searchByTitle(vector<Track> &index, string title)
{
    int last = index.size() - 1;
    int first = 0;

    while (first <= last)
    {
        int middle = (first + last) / 2;

        if (index[middle].title == title)
            return middle;

        else if (index[middle].title > title)
            last = middle - 1;

        else
            first = middle + 1;
    }
    return -1;
}
/**
 * uses binary search to find index in the vector of ssn being searched for
 *
 * @param index vector of pointers indexed to students vector.
 * @param social ssn being searched for
 */
int searchByAlbum(vector<Track *> &index, string album)
{
    int last = index.size() - 1;
    int first = 0;

    while (first <= last)
    {
        int middle = (first + last) / 2;

        if (index[middle]->album == album)
            return middle;

        else if (index[middle]->album > album)
            last = middle - 1;

        else
            first = middle + 1;
    }
    return -1;
}
/**
 * uses binary search to find index in the vector of the first name being searched for
 *
 * @param index vector of pointers indexed to students vector.
 * @param name first name being searched for
 */
int searchByArtist(vector<Track *> &index, string artist)
{
    int last = index.size() - 1;
    int first = 0;

    while (first <= last)
    {
        int middle = (first + last) / 2;

        if (index[middle]->artist == artist)
            return middle;

        else if (index[middle]->artist > artist)
            last = middle - 1;

        else
            first = middle + 1;

    }
    return -1;
}
