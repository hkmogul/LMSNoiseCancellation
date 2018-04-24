#pragma once
#include <JuceHeader.h>
#include <vector>
#include "DelayLine.h"
/// Implementation of a mono LMS adaptive filter
class LMSFilter
{
public:
	// constructor
	LMSFilter(int filtOrd = 30, int delayLen = 20, float m = 0.001f, int samplingRate = 44100, int samplesPerBlock = 480);

	// per sample output
	float processSample(float x);

	// prepare the FIR filter if there is a state change
	void prepare(int samplingRate, int samplesPerBlockExpected);

	~LMSFilter();

private:
	int filterOrder;
	int delayLength;
	float mu;
	DelayLine desiredOutputBuffer;
	DelayLine previousInputBuffer;
	juce::dsp::FIR::Filter<float> filter;
	//Array<float> prevCoefficients;
	std::vector<float> prevCoefficients;
};

