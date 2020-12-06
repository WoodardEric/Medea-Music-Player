#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <stdio.h>
#include "portaudio.h"
#include "MusicFile.h"

class AudioManager
{
public:
	AudioManager(MusicFile *file);
	~AudioManager();
	void openStream();
	void startStream();
	void stopStream();
	
	bool isStreaming();

	float getVolume() const { return mVolume; }
	void setVolume(float vol) { mVolume = vol; }

	int getBufferSize() const { return bufferSize; }
	int getFramesPerBuffer() const { return framesPerBuffer; }
	void setParameters(int numChannels, int bitsPerSample);
	
	PaStream *audioStream;
	int16_t *buffer;
	PaError err;

private:
	PaStreamParameters parameters;
	const PaDeviceInfo *deviceInfo;
	
	int framesPerBuffer;
	int bufferSize;
	float mVolume;
	const MusicFile *file;
};



#endif