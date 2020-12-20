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

//found a better way to handle changing files
//will remove once new aprouch is finalized 

//void AudioThread::changeFile()
//{
//	mPath = mNewPath;
//	delete mFile;
//	delete mAudio;
//	mFile = new MusicFile(mPath);
//	mAudio = new AudioManager(*mFile);
//	mTimeSlider->SetValue(0);
//	mTimeSlider->SetMax(mFile->getDataSize());
//	mIsOver = false;
//	mAudio->startStream();
//}
