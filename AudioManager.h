/**********************************************************************
 Medea: A Digital Music Player

 @file  AudioManger.h

 @brief:

 Manages the audio stream/tracking the playing audio file 
 and manages the sample buffer

 @author Eric Woodard
 @date   12/11/2020

 TODO: 
 *figure out best way to handle different sample sizes
 *Fix click at end of track
 **********************************************************************/
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "MusicFile.h"
#include "portaudio.h"
#include <stdio.h>

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

	PaError getErr() const { return err; }

	float getVolume() const { return mVolume; }
	void setVolume(const float vol) { mVolume = vol; }

	long getCounter() const { return mFrameCounter; }
	void setCounter(const long numFrames) { mFrameCounter = numFrames; }
	void increaseCounter() { mFrameCounter += mFramesPerBuffer; }
	void resetCounter() { mFrameCounter = 0; }

	int getBufferSize() const { return mBufferSize; }
	int getFramesPerBuffer() const { return mFramesPerBuffer; }

	void setParameters(const int numChannels, const int bitsPerSample);

	bool playAudio(MusicFile *file);
	void processBuffer();
	void clearBuffer();

	//TODO
	//void applyEq(float highpass, float high, float low);
	
private:
	void* *buffer;
	PaStream *audioStream;
	PaError err;
	PaStreamParameters parameters;
	const PaDeviceInfo *deviceInfo;
	int mFramesPerBuffer;
	int mBufferSize;
	float mVolume;
	long mFrameCounter;
	
	
};


#endif