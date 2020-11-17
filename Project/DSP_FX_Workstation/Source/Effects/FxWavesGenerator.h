/*
  ==============================================================================

    FxWavesGenerator.h
    Created: 17 Nov 2020 12:46:06pm
    Author:  usuario_nuevo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/

//==============================================================================
class FxWavesGeneratorProcessor : public ProcessorBase
{
public:
	FxWavesGeneratorProcessor()
	{
		oscillator.setFrequency(440.0f);
		oscillator.initialise([](float x) { return std::sin(x); });
	}

	void prepareToPlay(double sampleRate, int samplesPerBlock) override
	{
		dsp::ProcessSpec spec{ sampleRate, static_cast<uint32> (samplesPerBlock) };
		oscillator.prepare(spec);
	}

	void processBlock(AudioSampleBuffer& buffer, MidiBuffer&) override
	{
		dsp::AudioBlock<float> block(buffer);
		dsp::ProcessContextReplacing<float> context(block);
		oscillator.process(context);
	}

	void reset() override
	{
		oscillator.reset();
	}

	const String getName() const override { return "Waves Generator"; }

private:
	dsp::Oscillator<float> oscillator;
};



class FxWavesGenerator  : public juce::Component
{
public:
    FxWavesGenerator()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    ~FxWavesGenerator() override
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
        g.drawText ("FxWavesGenerator", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FxWavesGenerator)
};

