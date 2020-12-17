/**********************************************************************
 Medea: A Digital Music Player

 @file  AudioManger.cpp

 @brief:

 Manages the audio stream/tracking the playing audio file
 and manages the sample buffer

 @author Eric Woodard
 @date   12/11/2020

 **********************************************************************/
#include "AudioManager.h"
/*
* Default AudioManager constructor
*/
AudioManager::AudioManager() 
{
	audioStream = nullptr;
	short numChannels = 2;
	mFrameCounter = 0;
	mFramesPerBuffer = 1024;
	err = Pa_Initialize();
	parameters.device = Pa_GetDefaultOutputDevice();
	deviceInfo = Pa_GetDeviceInfo(parameters.device);
	mVolume = 1.0f;
		
	parameters.suggestedLatency = deviceInfo->defaultHighOutputLatency;
	parameters.hostApiSpecificStreamInfo = NULL;

	mBufferSize = (mFramesPerBuffer * numChannels);
	buffer = new void*[mBufferSize];	
}

/*
* Default AudioManager destructor. Terminates the audio stream
*/
AudioManager::~AudioManager()
{
	err = Pa_Terminate();
}
/*
* Opens and initilizes an audio stream to the sound card
* 
* @param numChannels number of channels from the audio file
* @param bitsPerSample number of bits each sample contain 
* @param sampleRate number of samples per seconds
*/
void AudioManager::openStream(const int numChannels, const int bitsPerSample, const int sampleRate)
{
	setParameters(numChannels, bitsPerSample);

	err = Pa_OpenStream(
		&audioStream,
		0,
		&parameters,
		sampleRate,
		mFramesPerBuffer,
		paClipOff,
		NULL, //no callback, use blocking API 
		NULL); //no callback, so no callback userData 
}
/*
* starts an audio stream and sets error status on return
*/
void AudioManager::startStream()
{
	err = Pa_StartStream(audioStream);
}
/*
* stops an audio stream and sets error status on return
*/
void AudioManager::stopStream()
{
	err = Pa_StopStream(audioStream);
}
/*
* closes an audio stream and sets error status on return
*/
void AudioManager::closeStream()
{
	err = Pa_CloseStream(audioStream);
}
/*
* aborts an audio stream and sets error status on return
*/
void AudioManager::Terminate()
{
	err = Pa_Terminate();
}
/*
* checks to see if audio stream is active
* 
* @return true if stream is active else returns false
*/
bool AudioManager::isStreaming() const
{
	return Pa_IsStreamActive(audioStream);
}
/*
* sets the stream parameters
*
* @param numChannels number channels in the audio data
* @param bitsPerSample number of bits in each sample
*/
void AudioManager::setParameters(const int numChannels, const int bitsPerSample)
{
	parameters.channelCount = numChannels;
	
		if (bitsPerSample == 16)
		{
			parameters.sampleFormat = paInt16;
		}
		else if (bitsPerSample == 8)
		{
			parameters.sampleFormat = paUInt8;
		}
		else if (bitsPerSample == 32)
		{
			parameters.sampleFormat = paInt32;
		}
		else
		{
			//error code
		}
	//}
	//else if (header->audioFormat == 3)
	//{
	//	if (header->bitsPerSample == 32)
	//	{
	//		parameters.sampleFormat = paFloat32;
	//	}
	//	else
	//	{
	//		//error code
	//	}
}
/*
* turns the error code into human readable text
*
* @return the error message from port audio
*/
string AudioManager::getErrorMessage() const
{
	return Pa_GetErrorText(err);
}
/*
* clears buffer by setting all values to 0
*/
void AudioManager::clearBuffer()
{
	for (int i = 0; i < mBufferSize; ++i)
	{
		buffer[i] = 0;
	}
}
/*
* fill buffer from a file, process audio, then sends it to the stream
* 
* @param *file being read
*/
bool AudioManager::playAudio(MusicFile *file)
{
	if (err != paNoError && err != paStreamIsStopped && err != paOutputUnderflowed)
	{
		return false;
	}
	if (file == nullptr)
	{
		err = Pa_IsStreamActive(audioStream);
		if (err == 0)
			stopStream();
		return true;
	}
	if (isStreaming() && file->getDataSize() - (mFrameCounter * file->getBlockAlighn()) >= mFramesPerBuffer * 3)
	{
		file->readSample(buffer, mBufferSize);
		processBuffer();
		err = Pa_WriteStream(audioStream, buffer, mFramesPerBuffer);
		increaseCounter();
		return true;
	}
	else if (mFrameCounter * file->getBlockAlighn() >= file->getDataSize())
	{
		return false;
	}

	return false;
}
/*
* processes each sample in the buffer
* currently only multiples a sample by the current volume
*/
void AudioManager::processBuffer()
{
	if (mVolume == 1.0)
	{
		return;
	}
	for (int i = 0; i < mBufferSize; ++i)
	{
		*static_cast<uint16_t*>(buffer[i]) *= mVolume;
	}
}

//TODO learn more maths

//void AudioManager::applyEq(float highpass, float high, float low)
//{
//	//int a = 0, b = 0, c = 0; //members of your effect, data is always maintained
//
//	//for (int i = 0; i < bufferSize; ++i)
//	//{
//	//	a += (13312 / file->getSampleRate()) * (buffer[i] - a); //x256
//	//	b += (1664.00 / file->getSampleRate()) * (buffer[i] - b); //x16
//	//	c += (104.000 / file->getSampleRate()) * (buffer[i] - c); //x1
//	//	buffer[i] = highpass * (buffer[i] - a) + high * (a - b) + low * (b - c) + 1 * c; //output is given for process function too
//	//}
//}
	