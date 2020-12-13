#include "AudioManager.h"

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
	buffer = new int16_t[mBufferSize];	
}

AudioManager::~AudioManager()
{
	err = Pa_Terminate();
}

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

void AudioManager::startStream()
{
	err = Pa_StartStream(audioStream);
}

void AudioManager::stopStream()
{
	err = Pa_StopStream(audioStream);
}

void AudioManager::closeStream()
{
	err = Pa_CloseStream(audioStream);
}

void AudioManager::Terminate()
{
	err = Pa_Terminate();
}

bool AudioManager::isStreaming() const
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

string AudioManager::getErrorMessage() const
{
	return Pa_GetErrorText(err);
}

void AudioManager::clearBuffer()
{
	for (int i = 0; i < mBufferSize; ++i)
	{
		buffer[i] = 0;
	}
}

bool AudioManager::playAudio(MusicFile *file)
{
	if (err != paNoError && err != paStreamIsStopped)
	{
		Terminate();
		return false;
	}

	if (file == nullptr)
	{
		err = Pa_IsStreamActive(audioStream);
		if (err == 0)
			stopStream();
		return true;
	}
	if (isStreaming() && mFrameCounter * 4 < file->getDataSize() + 1)
	{

		if (mFrameCounter * 4 < file->getDataSize() - (mFramesPerBuffer * 2))
		{
			file->readSample(buffer, mBufferSize);
		}
		
		processBuffer();
		err = Pa_WriteStream(audioStream, buffer, mFramesPerBuffer);
		increaseCounter();
		return true;
	}
	//change 4 to byte alighn
	else if (mFrameCounter * 4 >= file->getDataSize())
	{
		return false;
	}

	return false;
}
void AudioManager::processBuffer()
{
	for (int i = 0; i < mBufferSize; ++i)
	{
		buffer[i] *= mVolume;
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
	