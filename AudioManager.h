#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <stdio.h>

#include "portaudio.h"
#include "MusicFile.h"

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	//stream controls
	void openStream(const int numChannels, const int bitsPerSample, const int sampleRate);
	void startStream();
	void stopStream();
	void closeStream();
	void Terminate();

	string getErrorMessage() const;
	bool isStreaming() const;

	PaError getErr() { return err; }
	
	float getVolume() const { return mVolume; }
	void setVolume(float vol) { mVolume = vol; }

	void resetCounter() { mFrameCounter = 0; }
	long getCounter() const { return mFrameCounter; }
	void increaseCounter() { mFrameCounter += mFramesPerBuffer; }
	void setCounter(long numFrames) { mFrameCounter = numFrames; }

	int getBufferSize() const { return mBufferSize; }
	int getFramesPerBuffer() const { return mFramesPerBuffer; }
	void setParameters(int numChannels, int bitsPerSample);

	bool playAudio(MusicFile *file);
	void applyEq(float highpass, float high, float low);
	void clearBuffer();
	
	int16_t *buffer;
	PaStream *audioStream;

private:
	PaError err;
	PaStreamParameters parameters;
	const PaDeviceInfo *deviceInfo;
	int mFramesPerBuffer;
	int mBufferSize;
	float mVolume;
	long mFrameCounter;
	
	
};



#endif