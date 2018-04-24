#include "LMSFilter.h"
using namespace juce::dsp;
using namespace std;

LMSFilter::LMSFilter(int filtOrd, int delayLen, float m, int samplingRate, int samplesPerBlock)
{
	filterOrder = filtOrd;
	delayLength = delayLen;
	mu = m;
	desiredOutputBuffer = DelayLine(delayLength);
	previousInputBuffer = DelayLine(filterOrder);
	// initialize as all zeros

	prevCoefficients = vector<float>(filterOrder, 0.0f);
	*(filter.coefficients) = juce::dsp::FIR::Coefficients<float>(prevCoefficients.data(), filtOrd);
	prepare(samplingRate, samplesPerBlock);
}

float LMSFilter::processSample(float x)
{
	// step 0 - handle delay lines
	float s = desiredOutputBuffer.process(x);
	// don't need the output of this one
	previousInputBuffer.process(x);

	// step 1 - current sample output
	float y = filter.processSample(x);

	// step 2 - calculate error
	float e = y - s;

	// step 3 update filter coefficients
	auto *coefPtr = filter.coefficients->getRawCoefficients();
	for (int i = 0; i < filterOrder; i++)
	{
		coefPtr[i] = coefPtr[i] + 2 * mu * e *previousInputBuffer.readReverse(i);
	}
	
	// step 4- return previously calculated output
	return y;
}

void LMSFilter::prepare(int samplingRate, int samplesPerBlockExpected)
{
	ProcessSpec spec;
	spec.maximumBlockSize = samplesPerBlockExpected;
	spec.sampleRate = samplingRate;
	spec.numChannels = 1;
	filter.prepare(spec);
	//*(filter.coefficients) = dsp::FIR::Coefficients<float>(prevCoefficients.data(), filterOrder);
}

LMSFilter::~LMSFilter()
{
}
