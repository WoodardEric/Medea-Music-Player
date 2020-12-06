#include "AudioManager.h"

AudioManager::AudioManager(MusicFile *file) : file(file)
{

	framesPerBuffer = 1024;
	err = Pa_Initialize();
	parameters.device = Pa_GetDefaultOutputDevice();
	deviceInfo = Pa_GetDeviceInfo(parameters.device);
	mVolume = 1.0f;
	
	parameters.suggestedLatency = deviceInfo->defaultHighOutputLatency;
	parameters.hostApiSpecificStreamInfo = NULL;

	/*int time = numSamples / header->sampleRate;*/
	//int numBytes = framesPerBuffer * header->numChannels * header->bitsPerSample;

	bufferSize = (framesPerBuffer * file->getNumChannels());
	buffer = new int16_t[bufferSize];
	
}

AudioManager::~AudioManager()
{
	err = Pa_Terminate();
}

void AudioManager::openStream()
{
	setParameters(file->getNumChannels(), file->getBitsPerSample());
	err = Pa_OpenStream(
		&audioStream,
		0,
		&parameters,
		file->getSampleRate(),
		framesPerBuffer,
		paClipOff,
		NULL, /* no callback, use blocking API */
		NULL); /* no callback, so no callback userData */
}

void AudioManager::startStream()
{
	err = Pa_StartStream(audioStream);
}

void AudioManager::stopStream()
{
	err = Pa_StopStream(audioStream);
}



bool AudioManager::isStreaming()
{
	return Pa_IsStreamActive(audioStream);
}

void AudioManager::setParameters(int numChannels, int bitsPerSample)
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