/*
  ==============================================================================

    FxHighPassFilter.h
    Created: 17 Nov 2020 12:38:48pm
    Author:  usuario_nuevo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/

//==============================================================================
class FxHighPassProcessor : public ProcessorBase
{
public:
	FxHighPassProcessor() {}

	void prepareToPlay(double sampleRate, int samplesPerBlock) override
	{
		*hpfilter.state = *dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 1000.0f);

		dsp::ProcessSpec spec{ sampleRate, static_cast<uint32> (samplesPerBlock), 2 };
		hpfilter.prepare(spec);
	}

	void processBlock(AudioSampleBuffer& buffer, MidiBuffer&) override
	{
		dsp::AudioBlock<float> block(buffer);
		dsp::ProcessContextReplacing<float> context(block);
		hpfilter.process(context);
	}

	void reset() override
	{
		hpfilter.reset();
	}

	const String getName() const override { return "HighPass Filter"; }

private:
	dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> hpfilter;
};


class FxHighPassFilter  : public juce::Component
{
public:
    FxHighPassFilter()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    ~FxHighPassFilter() override
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
        g.drawText ("FxHighPassFilter", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FxHighPassFilter)
};
