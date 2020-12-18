#ifndef AUDIOTHREAD_H
#define AUDIOTHREAD_H

#include "MusicFile.h"
#include "AudioManager.h"
#include "Playlist.h"
#include <wx/wx.h>
#include "portaudio.h"

#include <string>

using std::string;

class AudioThread : public wxThread
{
public:
	AudioThread(string path, const wxSlider *volSlider, wxSlider *timeSlider);
	virtual void *Entry();
	void setPath(string path) { mNewPath = path; }
	
private:
	void changeFile();
	string mPath;
	string mNewPath;
	const wxSlider *mVolSlider;
	wxSlider *mTimeSlider;
	MusicFile *mFile;
	AudioManager *mAudio;
};

#endif