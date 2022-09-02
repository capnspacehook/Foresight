#pragma once

#include "JuceHeader.h"

class VoiceManager {
public:
	VoiceManager();
	~VoiceManager();
	/// <summary>
	/// Returns a new MidiBuffer containing the events from the input buffer,
	/// distributed across MIDI channels so that each channel is strictly monophonic.
	/// </summary>
	/// <param name="buffer">The input MidiBuffer</param>
	/// <returns>The processed buffer</returns>
	juce::MidiBuffer processBuffer(const juce::MidiBuffer& buffer);

	/// <summary>
	/// Gets the amount of currently playing voices after processing the last buffer.
	/// </summary>
	/// <returns>The amount of playing voices</returns>
	int getCurrentVoiceCount();

	/// <summary>
	/// Resets the internal state of the VoiceManager. This should be called when playback is stopped.
	/// </summary>
	void reset();

private:
	std::optional<int> heldNote;
	int currentVoiceCount = 0;
};