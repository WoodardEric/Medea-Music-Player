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
	void setPath(string path) { mNewPath = path; }
	void setVolume(float vol) { mAudio->setVolume(vol); }
	long getCounter() const { return mAudio->getCounter(); }
	void setFilePos(long bytes) { filePos = bytes; }
	//bool getisPlaying
private:
	void changeFile();
	string mPath;
	string mNewPath;
	
	wxSlider *mTimeSlider;
	MusicFile *mFile;
	AudioManager *mAudio;
	long filePos;
	bool isPlaying;
};

#endif