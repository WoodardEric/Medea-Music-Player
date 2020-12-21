/**********************************************************************
 Medea: A Digital Music Player

 @file  AudioThread.h

 @brief:

 Thread that reads audio from a file and sends the buffer to
 the audio stream

 @author Eric Woodard
 @date   12/18/2020

 **********************************************************************/
#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include "AudioFile.h"
#include "AudioManager.h"
#include "Playlist.h"
#include <wx/wx.h>
#include "portaudio.h"

#include <string>

using std::string;

class AudioThread : public wxThread
{
public:
	AudioThread(string path, wxSlider *timeSlider);
	virtual void *Entry();
	
	void setVolume(float vol) { mAudio->setVolume(vol); }
	long getCounter() const { return mAudio->getCounter(); }
	void setCounter(long bytes) { mAudio->setCounter(mTimeSlider->GetValue() / 4); }
	void setFilePos(long bytes) { mfileUpdatePos = bytes; }
	bool isOver() const { return mIsOver; }

private:
	wxSlider *mTimeSlider;
	MusicFile *mFile;
	AudioManager *mAudio;

	string mPath; //current file
	long mfileUpdatePos; //location of bytes file should seek to
	bool mIsOver; //true if end if audio data reached in file

	//void changeFile();
};

#endif