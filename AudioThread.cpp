#include "AudioThread.h"

AudioThread::AudioThread(string path, const wxSlider *volSlider, wxSlider *timeSlider)
	: mPath(path), mVolSlider(volSlider), mTimeSlider(timeSlider)
{
	mNewPath = mPath;
	mFile = new MusicFile(mPath);
	mAudio = new AudioManager(*mFile);
}
void *AudioThread::Entry()
{
	mTimeSlider->SetMax(mFile->getDataSize());
	long songPos = 0;
	mAudio->startStream();
	while (true)
	{
		while (mAudio->playAudio(mFile))
		{
			long timslPos = mTimeSlider->GetValue();
			if (songPos != timslPos)
			{
				mFile->seek(mTimeSlider->GetValue());
				mAudio->setCounter(mTimeSlider->GetValue() / 4);
			}

			mAudio->setVolume(mVolSlider->GetValue() / 100.0f);
			mTimeSlider->SetValue(mAudio->getCounter() * 4);
			songPos = mAudio->getCounter() * 4;
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
	mAudio->startStream();
}
