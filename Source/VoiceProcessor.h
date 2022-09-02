#pragma once

#include "JuceHeader.h"
#include "BufferedNote.h"
#include "BufferedMidiMessage.h"

class VoiceProcessor {
public:
	VoiceProcessor(int bufferSizeSamples) : bufferSizeSamples(bufferSizeSamples) {}
	juce::MidiBuffer processBuffer(const juce::MidiBuffer& buffer, int channel, int lengthSamples);
	void reset();
private:
	int bufferSizeSamples;
	unsigned long long readHeadPosition = 0;

	std::vector<BufferedNote> bufferedNotes;
	std::optional<BufferedNote> lastWrittenNote;
	BufferedNote* heldNoteAtWritePosition = nullptr;
	BufferedNote* heldNoteAtReadPosition = nullptr;

	std::vector<BufferedMidiMessage> unprocessedBuffer;

	unsigned long long getReadPosition();
	unsigned long long getWritePosition();

	std::vector<juce::MidiMessage> processSample(const std::optional<std::vector<juce::MidiMessage>> enteredMessages, int channel);
};