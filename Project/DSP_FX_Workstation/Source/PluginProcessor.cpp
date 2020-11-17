/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Helper.h"


//==============================================================================
Dsp_fx_workstationAudioProcessor::Dsp_fx_workstationAudioProcessor()
     : AudioProcessor (BusesProperties()
		 .withInput("Input", juce::AudioChannelSet::stereo(), true)
		 .withOutput("Output", juce::AudioChannelSet::stereo(), true)
	 ),
	mainProcessor(new AudioProcessorGraph()),
	muteInput(new AudioParameterBool("mute", "Mute Input", true)),
	bypassAll(new AudioParameterBool("bypass", "Bypass All", false)),
	processorSlot1(new AudioParameterChoice("slot1", "Slot 1", processorChoices, 0)),
	processorSlot2(new AudioParameterChoice("slot2", "Slot 2", processorChoices, 0)),
	processorSlot3(new AudioParameterChoice("slot3", "Slot 3", processorChoices, 0)),
	processorSlot4(new AudioParameterChoice("slot4", "Slot 4", processorChoices, 0)),
	bypassSlot1(new AudioParameterBool("bypass1", "Bypass 1", false)),
	bypassSlot2(new AudioParameterBool("bypass2", "Bypass 2", false)),
	bypassSlot3(new AudioParameterBool("bypass3", "Bypass 3", false)),
	bypassSlot4(new AudioParameterBool("bypass4", "Bypass 4", false))
	// ADD
{
	addParameter(muteInput);
	addParameter(bypassAll);

	addParameter(processorSlot1);
	addParameter(processorSlot2);
	addParameter(processorSlot3);
	addParameter(processorSlot4);

	addParameter(bypassSlot1);
	addParameter(bypassSlot2);
	addParameter(bypassSlot3);
	addParameter(bypassSlot4);
	// ADD
}

Dsp_fx_workstationAudioProcessor::~Dsp_fx_workstationAudioProcessor()
{
}

//==============================================================================
const juce::String Dsp_fx_workstationAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Dsp_fx_workstationAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Dsp_fx_workstationAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Dsp_fx_workstationAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Dsp_fx_workstationAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Dsp_fx_workstationAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Dsp_fx_workstationAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Dsp_fx_workstationAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Dsp_fx_workstationAudioProcessor::getProgramName (int index)
{
    return {};
}

void Dsp_fx_workstationAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Dsp_fx_workstationAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	mainProcessor->setPlayConfigDetails(getMainBusNumInputChannels(),
		getMainBusNumOutputChannels(),
		sampleRate, samplesPerBlock);

	mainProcessor->prepareToPlay(sampleRate, samplesPerBlock);

	initialiseGraph();
}

void Dsp_fx_workstationAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
	mainProcessor->releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Dsp_fx_workstationAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
	if (layouts.getMainInputChannelSet() == AudioChannelSet::disabled()
		|| layouts.getMainOutputChannelSet() == AudioChannelSet::disabled())
		return false;
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Dsp_fx_workstationAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }

	updateGraph();

	mainProcessor->processBlock(buffer, midiMessages);
}

//==============================================================================
bool Dsp_fx_workstationAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Dsp_fx_workstationAudioProcessor::createEditor()
{
	// SETUP GUI DEBUG MODE
	if (customGui == true)
	{
		return new Dsp_fx_workstationAudioProcessorEditor(*this);
	}
	else
	{
		return new GenericAudioProcessorEditor(*this);
	}

}

//==============================================================================
void Dsp_fx_workstationAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Dsp_fx_workstationAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Dsp_fx_workstationAudioProcessor();
}
