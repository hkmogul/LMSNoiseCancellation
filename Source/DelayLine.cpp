#include "DelayLine.h"
#include <cstring>
#include <JuceHeader.h>

DelayLine::DelayLine(int len)
{
	currentPos = 0;
	dLen = len;
	memset(buffer, 0, MAXLEN * sizeof(float));
}

float DelayLine::process(float x)
{
	int writePos = (currentPos + dLen) % MAXLEN;
	buffer[writePos] = x;
	float y = buffer[currentPos];
	// update read position
	currentPos = (currentPos + 1) % MAXLEN;
	return y;
}

float DelayLine::readReverse(int idx)
{
	// idx = 0 corresponds to write position
	// idx = dLen corresponds to read position
	// should get buffer[dLen - idx]
	// read from end of buffer
	if (idx > dLen)
	{
		return 0.0f;
	}



	int pos = (currentPos + dLen - idx) % MAXLEN;
	return buffer[pos];

}

float DelayLine::read(int idx)
{
	int readIdx = (currentPos + idx) % MAXLEN;
	return buffer[readIdx];
}



DelayLine::~DelayLine()
{
}
