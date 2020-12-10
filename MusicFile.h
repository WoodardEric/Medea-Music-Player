#ifndef MUSICFILE_H
#define MUSICFILE_H

#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::ios;
using std::fstream;
using std::ios_base;

struct AudioHeader
{
	AudioHeader(fstream &inFile)
	{
		inFile.read(reinterpret_cast<char *>(&chunkID), sizeof(uint8_t) * 4);
		inFile.read(reinterpret_cast<char *>(&chunkSize), sizeof(uint32_t));

		uint8_t format[4];
		inFile.read(reinterpret_cast<char *>(&format), sizeof(uint8_t) * 4);

		inFile.read(reinterpret_cast<char *>(&subChunk1ID), sizeof(uint8_t) * 4);
		inFile.read(reinterpret_cast<char *>(&subChunk1Size), sizeof(uint32_t));

		inFile.read(reinterpret_cast<char *>(&audioFormat), sizeof(uint16_t));
		inFile.read(reinterpret_cast<char *>(&numChannels), sizeof(uint16_t));
		inFile.read(reinterpret_cast<char *>(&sampleRate), sizeof(uint32_t));
		inFile.read(reinterpret_cast<char *>(&byteRate), sizeof(uint32_t));

		inFile.read(reinterpret_cast<char *>(&blockAlighn), sizeof(uint16_t));
		inFile.read(reinterpret_cast<char *>(&bitsPerSample), sizeof(uint16_t));
		if (subChunk1Size == 18)
		{
			uint16_t extraSize;
			inFile.read(reinterpret_cast<char *>(&extraSize), sizeof(uint16_t));
			if (extraSize == 22)
			{
				//error can't read WAVE_FORMAT_EXTENSIBLE
			}
		}
		char data[]{ 'd', 'a', 't', 'a' };
		inFile.read(reinterpret_cast<char *>(&subChunk2ID), sizeof(uint8_t) * 4);
		while (std::strncmp(subChunk2ID, data, 4) != 0)
		{
			inFile.read(reinterpret_cast<char *>(&subChunk2Size), sizeof(uint32_t));
			int junk;
			inFile.read(reinterpret_cast<char *>(&junk), sizeof(uint8_t) * subChunk2Size);
			inFile.read(reinterpret_cast<char *>(&subChunk2ID), sizeof(uint8_t) * 4);
		}

		inFile.read(reinterpret_cast<char *>(&subChunk2Size), sizeof(uint32_t));
		numSamples = subChunk2Size / ((bitsPerSample / 8) * numChannels);
		dataPos = inFile.tellg();
	}

	uint8_t chunkID[4];
	uint32_t chunkSize;

	uint8_t subChunk1ID[4];
	uint32_t subChunk1Size;

	uint16_t audioFormat;
	uint16_t numChannels;

	uint32_t sampleRate;
	uint32_t byteRate;
	uint16_t blockAlighn;
	uint16_t bitsPerSample;

	char subChunk2ID[4];
	uint32_t subChunk2Size;
	int numSamples;

	int dataPos;
};

class MusicFile
{
public:
	MusicFile();
	MusicFile(string path);
	~MusicFile();
	void readSample(int16_t buffer[], int bufferSize);

	uint32_t getSampleRate()  const { return header.sampleRate; }
	int getNumChannels() const { return header.numChannels; }
	uint16_t getBitsPerSample() const { return header.bitsPerSample; }
	long getDataSize() const { return header.subChunk2Size; }
	int getCurrTrackTime(const long &numFrames);
	void seek(long bytes);
	fstream& getFileStream() { return fileStream; }

	std::streampos getDataPos() { return header.dataPos; }
	int getEndPos() { return header.dataPos + header.subChunk2Size; }
	int getCurrPos() { return fileStream.tellg(); }
	
private:
	fstream fileStream;
	AudioHeader header;
	
	
};



#endif

