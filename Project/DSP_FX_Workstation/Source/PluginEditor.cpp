/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Dsp_fx_workstationAudioProcessorEditor::Dsp_fx_workstationAudioProcessorEditor (Dsp_fx_workstationAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

	// Reclame the parameters and assign to gui controls
	for (auto* parameter : processor.getParameters())
	{
		if (auto* pWithID = dynamic_cast<juce::RangedAudioParameter*>(parameter))
		{
			if (pWithID->paramID == "slot1")
			{
				comboAttachment = std::make_unique<juce::ComboBoxParameterAttachment>(*pWithID, cbox1);
				cbox1.addItemList(pWithID->getAllValueStrings(), 2);
			}
			if (pWithID->paramID == "slot2")
			{
				comboAttachment2 = std::make_unique<juce::ComboBoxParameterAttachment>(*pWithID, cbox2);
				cbox2.addItemList(pWithID->getAllValueStrings(), 1);
			}
			if (pWithID->paramID == "slot3")
			{
				comboAttachment3 = std::make_unique<juce::ComboBoxParameterAttachment>(*pWithID, cbox3);
				cbox3.addItemList(pWithID->getAllValueStrings(), 1);
			}
			if (pWithID->paramID == "slot4")
			{
				comboAttachment4 = std::make_unique<juce::ComboBoxParameterAttachment>(*pWithID, cbox4);
				cbox4.addItemList(pWithID->getAllValueStrings(), 1);
			}
			if (pWithID->paramID == "bypass1")
			{
				buttonAttachment = std::make_unique<juce::ButtonParameterAttachment>(*pWithID, cb1bypass);
				cb1bypass.setButtonText("Bypass");
				break;
			}
		}
	}



	//----------------------------------------------------------------------
// ADD first combobox > Param > Choice processor node

	//cbox1.addSeparator();
	//cbox1.addItem("ADN Distortion Kit", 9);
	//cbox1.addSeparator();
	//cbox1.addItem("Alex Filters", 10);
	//cbox1.addItem("EQ Pro V2", 11);
	//cbox1.addItem("Mega Drive", 12);
	// ########################################## EDIT


	// ##########################################
	cbox1.setJustificationType(Justification::centred);
	//cbox1.setFont(juce::Font(16.0f, juce::Font::bold));
	cbox1.setSelectedItemIndex(0);

	addAndMakeVisible(cbox1);

	cb1mute.setButtonText("Mute");
	addAndMakeVisible(cb1mute);

	cb1solo.setButtonText("Solo");
	addAndMakeVisible(cb1solo);

	cb1bypass.setButtonText("B");
	addAndMakeVisible(cb1bypass);

	//----------------------------------------------------------------------

	cbox2.setSelectedItemIndex(0);
	cbox2.setJustificationType(Justification::centred);
	addAndMakeVisible(cbox2);

	//----------------------------------------------------------------------

	cbox3.setSelectedItemIndex(0);
	cbox3.setJustificationType(Justification::centred);
	addAndMakeVisible(cbox3);

	//----------------------------------------------------------------------

	cbox4.setSelectedItemIndex(0);
	cbox4.setJustificationType(Justification::centred);
	addAndMakeVisible(cbox4);


    setSize (1250, 250);
}

Dsp_fx_workstationAudioProcessorEditor::~Dsp_fx_workstationAudioProcessorEditor()
{
}

//==============================================================================
void Dsp_fx_workstationAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
	g.fillAll(juce::Colours::transparentBlack);
    //g.setColour (juce::Colours::white);
   // g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Dsp_fx_workstationAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	// PLACE Combobox 1 + Buttons
	cbox1.setBounds(110, 150, 120, 20);
	cb1mute.setBounds(110, 130, 40, 15);
	cb1solo.setBounds(150, 130, 40, 15);
	cb1bypass.setBounds(190, 130, 40, 15);

	cbox2.setBounds(250, 150, 120, 20);
	cbox3.setBounds(390, 150, 120, 20);
	cbox4.setBounds(530, 150, 120, 20);
}
