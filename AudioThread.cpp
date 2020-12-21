/**********************************************************************
 Medea: A Digital Music Player

 @file  AudioThread.cpp

 @brief:

 Thread that reads audio from a file and sends the buffer to 
 the audio stream
 

 @author Eric Woodard
 @date   12/18/2020

 **********************************************************************/
#include "AudioThread.h"
/*
* Audio Thread constructor
* 
* @param path the file location on the computer
* @param timeSlider pointer to timeSlider on main window
*/
AudioThread::AudioThread(string path, wxSlider *timeSlider)
	: mPath(path), mTimeSlider(timeSlider)
{
	//mNewPath = mPath;
	mFile = new MusicFile(mPath);
	mAudio = new AudioManager(*mFile);
	mfileUpdatePos = -1;
	mIsOver = false;
}
/*
* Threads point of entry. Loops reading a file and sending audio to stream
* Lasts forever unless destoryed by main thread or the program ends
* 
*/
void *AudioThread::Entry()
{
	mTimeSlider->SetMax(mFile->getDataSize());
	mAudio->startStream();

	while (!TestDestroy())
	{
		while (mAudio->playAudio(mFile) && !TestDestroy())
		{
			
			if (mfileUpdatePos != -1)
			{
				mFile->seek(mfileUpdatePos);
				mAudio->setCounter(mTimeSlider->GetValue() / 4);
				mfileUpdatePos = -1;
			}
			
			Sleep(5);
		}
		mIsOver = true;
		Sleep(10);		
	}
	return NULL;
}
