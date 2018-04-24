#pragma once
#define MAXLEN 2048
class DelayLine
{
public:
	DelayLine(int len =30);

	float process(float x);
	float read(int idx);
	float readReverse(int idx);

	~DelayLine();
private:
	float buffer[MAXLEN];
	int dLen;
	int currentPos;
};

