#pragma once
#include <JuceHeader.h>
#include <vector>
#include "DelayLine.h"
class LMSFilter
{
public:
	LMSFilter(int filtOrd = 30, int delayLen = 20, float m = 0.001f, int samplingRate = 44100, int samplesPerBlock = 480);
	float processSample(float x);
	void prepare(int samplingRate, int samplesPerBlockExpected);

	~LMSFilter();

private:
	int filterOrder;
	int delayLength;
	float mu;
	DelayLine desiredOutputBuffer;
	DelayLine previousInputBuffer;
	juce::dsp::FIR::Filter<float> filter;
	std::vector<float> prevCoefficients;
};

