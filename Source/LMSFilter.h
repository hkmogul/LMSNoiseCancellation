#pragma once
#include <JuceHeader.h>
#include <vector>
#include "DelayLine.h"
class LMSFilter
{
public:
	LMSFilter(int filtOrd, int delayLen, float m, int samplingRate, int samplesPerBlock);
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

