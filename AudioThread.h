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
	//void setPath(string path) { mNewPath = path; }
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
	//string mNewPath; //path to new file
	long mfileUpdatePos; //location of bytes file should seek to
	bool mIsOver; //true if end if audio data reached in file

	//void changeFile();
};

#endif