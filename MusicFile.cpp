#include "MusicFile.h"

MusicFile::MusicFile(string path) : fileStream(path, ios::in | ios::binary), header(fileStream)
{
	//fileStream.open(path, ios::in | ios::binary);
	
}
MusicFile::~MusicFile()
{
	fileStream.close();
	//delete header;
}
void MusicFile::readSample(int16_t buffer[], int bufferSize)
{
	fileStream.read(reinterpret_cast<char *>(buffer), sizeof(int16_t) * bufferSize);
}

int MusicFile::getCurrTrackTime(const long &numFrames)
{
	long bytes = numFrames * header.blockAlighn;
	return bytes / (header.sampleRate * header.numChannels * header.bitsPerSample / 8);
}

void MusicFile::seek(long bytes)
{
	fileStream.seekg(header.dataPos);
	fileStream.seekg(bytes, ios_base::cur);
}