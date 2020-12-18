/**********************************************************************
 Medea: A Digital Music Player

 @file  MusicFile.cpp

 @brief:

 manages reading audio files

 @author Eric Woodard
 @date   12/11/2020

 **********************************************************************/
#include "MusicFile.h"

/*
* MusicFile constructor
* 
* @param path loction of the file on the computrer
*/
MusicFile::MusicFile(string path)
	
{
	//fileStream.open(path, ios::in | ios::binary);
}
/*
* MusicFile dedstructor, closes file stream
*/
MusicFile::~MusicFile()
{
	fileStream.close();
}
/*
* reads audio samples into the buffer depending on sample size in bits
* 
* @param buffer audio sample buffer that is passed to the audio stream
* @param bufferSize the size of the buffer array
*/
void MusicFile::readSample(void *buffer, int bufferSize)
{
	if (header.bitsPerSample == 16)
	{
		fileStream.read(reinterpret_cast<char *>(buffer), sizeof(uint16_t) * bufferSize);
	}
	else if (header.bitsPerSample == 32)
	{
		fileStream.read(reinterpret_cast<char *>(buffer), sizeof(uint32_t) * bufferSize);
	}
	else if (header.bitsPerSample == 8)
	{
		fileStream.read(reinterpret_cast<char *>(buffer), sizeof(uint8_t) * bufferSize);
	}
}
/*
* converts a number of frames into seconds
* 
* @param numFrames amount of frames being converted
* @returns seconds of audio data contained in the frames
*/
int MusicFile::getCurrTrackTime(const long &numFrames)
{
	long bytes = numFrames * header.blockAlighn;
	return bytes / (header.sampleRate * header.numChannels * header.bitsPerSample / 8);
}
/*
* changes the cursor location in the file by a certain number of bytes
*
* @param bytes the number of bytes to move the cursor loction in the file
*/
void MusicFile::seek(long bytes)
{
	fileStream.seekg(header.dataPos);
	if (bytes > 0)
		fileStream.seekg(bytes, ios_base::cur);
}
/*
* converts a number of frames into seconds
*
* @param numFrames amount of frames being converted
* @returns seconds of audio data contained in the frames
*/
string MusicFile::timeToString(const long &numFrames)
{
	int n = getCurrTrackTime(numFrames);
	int min = n / 60;
	n = n % 60;
	int sec = n;
	std::ostringstream stream;
	std::string trackTime;
	
	stream << min << ':';
	if (sec < 10)
		stream << 0 << sec;
	else
		stream << sec;

	return stream.str();
}
/*
* converts seconds into a string displaying minutes:seconds
*
*/
string MusicFile::timeToString()
{
	int n = header.duration;
	int min = n / 60;
	n = n % 60;
	int sec = n;
	std::ostringstream stream;

	stream << min << ':';
	if (sec < 10)
		stream << 0 + sec;
	else
		stream << sec;

	return stream.str();
}