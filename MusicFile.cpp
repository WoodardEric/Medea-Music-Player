#include "MusicFile.h"

MusicFile::MusicFile(string path) 
	: fileStream(path, ios::in | ios::binary), header(fileStream)
{
	//fileStream.open(path, ios::in | ios::binary);
	
}
MusicFile::~MusicFile()
{
	fileStream.close();
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
	if (bytes > 0)
		fileStream.seekg(bytes, ios_base::cur);
}

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

string MusicFile::timeToString()
{
	int n = header.duration;
	int min = n / 60;
	n = n % 60;
	int sec = n;
	std::ostringstream stream;
	std::string trackTime;

	stream << min << ':';
	if (sec < 10)
		stream << 0 + sec;
	else
		stream << sec;

	return stream.str();
}