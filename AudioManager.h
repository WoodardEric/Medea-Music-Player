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
	void closeStream();
	void Terminate();
	string getErrorMessage();

	bool isStreaming();

	float getVolume() const { return mVolume; }
	void setVolume(float vol) { mVolume = vol; }

	void resetCounter() { mFrameCounter = 0; }
	long getCounter() const { return mFrameCounter; }
	void increaseCounter() { mFrameCounter += framesPerBuffer; }
	void setCounter(long numFrames) { mFrameCounter = numFrames; }

	int getBufferSize() const { return bufferSize; }
	int getFramesPerBuffer() const { return framesPerBuffer; }
	void setParameters(int numChannels, int bitsPerSample);
	void applyEq(float highpass, float high, float low);
	void clearBuffer();

	PaStream *audioStream;
	int16_t *buffer;
	PaError err;
	
private:
	PaStreamParameters parameters;
	const PaDeviceInfo *deviceInfo;
	int framesPerBuffer;
	int bufferSize;
	float mVolume;
	long mFrameCounter;
	const MusicFile *file;
	
};



#endif