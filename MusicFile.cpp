#include "MusicFile.h"

MusicFile::MusicFile(string path)
{
	fileStream.open(path, ios::in | ios::binary);
	header = new AudioHeader(fileStream);
}
MusicFile::~MusicFile()
{
	fileStream.close();
	delete header;
}
void MusicFile::readSample(int16_t buffer[], int bufferSize)
{
	fileStream.read(reinterpret_cast<char *>(buffer), sizeof(int16_t) * bufferSize);
}