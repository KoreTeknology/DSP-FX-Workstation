/*
  ==============================================================================

    FxLowPassFilter.h
    Created: 17 Nov 2020 12:38:29pm
    Author:  usuario_nuevo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
//==============================================================================
class FxLowPassFilterProcessor : public ProcessorBase
{
public:
	FxLowPassFilterProcessor() {}

	void prepareToPlay(double sampleRate, int samplesPerBlock) override
	{
		*lpfilter.state = *dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, 200.0f);

		dsp::ProcessSpec spec{ sampleRate, static_cast<uint32> (samplesPerBlock), 2 };
		lpfilter.prepare(spec);
	}

	void processBlock(AudioSampleBuffer& buffer, MidiBuffer&) override
	{
		dsp::AudioBlock<float> block(buffer);
		dsp::ProcessContextReplacing<float> context(block);
		lpfilter.process(context);
	}

	void reset() override
	{
		lpfilter.reset();
	}

	const String getName() const override { return "LowPass Filter"; }

private:
	dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> lpfilter;
};


class FxLowPassFilter  : public juce::Component
{
public:
    FxLowPassFilter()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    ~FxLowPassFilter() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (juce::Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (juce::Colours::white);
        g.setFont (14.0f);
        g.drawText ("FxLowPassFilter", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FxLowPassFilter)
};
