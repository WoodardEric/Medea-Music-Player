#include "AudioThread.h"

AudioThread::AudioThread(string path, wxSlider *timeSlider)
	: mPath(path), mTimeSlider(timeSlider)
{
	mNewPath = mPath;
	mFile = new MusicFile(mPath);
	mAudio = new AudioManager(*mFile);
	filePos = -1;
	isPlaying = true;
}
void *AudioThread::Entry()
{
	mTimeSlider->SetMax(mFile->getDataSize());
	mAudio->startStream();

	while (true)
	{
		while (mAudio->playAudio(mFile) && !TestDestroy())
		{
			if (filePos != -1)
			{
				mFile->seek(filePos);
				mAudio->setCounter(mTimeSlider->GetValue() / 4);
				filePos = -1;
			}

			Sleep(5);
			if (mPath != mNewPath)
			{
				changeFile();
			}
		}

		Sleep(40);
		if (mPath != mNewPath)
		{
			changeFile();
		}
		
	}
	return NULL;
}
void AudioThread::changeFile()
{
	mPath = mNewPath;
	delete mFile;
	delete mAudio;
	mFile = new MusicFile(mPath);
	mAudio = new AudioManager(*mFile);
	mTimeSlider->SetMax(mFile->getDataSize());
	mTimeSlider->SetValue(0);
	mAudio->startStream();
}
