/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Dsp_fx_workstationAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Dsp_fx_workstationAudioProcessorEditor (Dsp_fx_workstationAudioProcessor&);
    ~Dsp_fx_workstationAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
	ComboBox cbox1;
	ComboBox cbox2;
	ComboBox cbox3;
	ComboBox cbox4;

	TextButton cb1mute;
	TextButton cb1solo;
	ToggleButton cb1bypass;

	ToggleButton toggle;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Dsp_fx_workstationAudioProcessor& audioProcessor;

	// COMBOBOX ATTACHMENTS
	std::unique_ptr<juce::ComboBoxParameterAttachment> comboAttachment;
	std::unique_ptr<juce::ComboBoxParameterAttachment> comboAttachment2;
	std::unique_ptr<juce::ComboBoxParameterAttachment> comboAttachment3;
	std::unique_ptr<juce::ComboBoxParameterAttachment> comboAttachment4;

	// BUTTONS ATTACHMENTS
	std::unique_ptr<juce::ButtonParameterAttachment> buttonAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Dsp_fx_workstationAudioProcessorEditor)
};
