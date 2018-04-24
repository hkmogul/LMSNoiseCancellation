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
	prevCoefficients = vector<float>(filterOrder, 0.0f);
	prepare(samplingRate, samplesPerBlock);
}

float LMSFilter::processSample(float x)
{
	// step 0 - handle delay lines
	float s = desiredOutputBuffer.process(x);
	previousInputBuffer.process(x);

	// step 1 - current sample output
	float y = filter.processSample(x);

	// step 2 - calculate error
	float e = y - s;

	// step 3 update filter coefficients
	for (int i = 0; i < filterOrder; i++)
	{
		prevCoefficients[i] = prevCoefficients[i] + 2 * mu * e *previousInputBuffer.readReverse(i);
	}
	*(filter.coefficients) = dsp::FIR::Coefficients<float>(prevCoefficients.data(), filterOrder);


	return y;
}

void LMSFilter::prepare(int samplingRate, int samplesPerBlockExpected)
{
	ProcessSpec spec;
	spec.maximumBlockSize = samplesPerBlockExpected;
	spec.sampleRate = samplingRate;
	spec.numChannels = 1;
	filter.prepare(spec);
	*(filter.coefficients) = dsp::FIR::Coefficients<float>(prevCoefficients.data(), filterOrder);
	
}

LMSFilter::~LMSFilter()
{
}
