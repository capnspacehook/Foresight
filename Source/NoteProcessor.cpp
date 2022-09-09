#include "NoteProcessor.h"

NoteProcessor::NoteProcessor(BufferedNote* note, Configuration* configuration, const std::unordered_set<std::string>& tags, int channel)
{
	this->target = note;
	this->sampleRate = configuration->getSampleRate();
	this->channel = channel;
	
	for (const auto& tag : tags) {
		std::optional<OutputListNode> node = configuration->getOutputNode(tag);
		if (node.has_value()) {
			switch (node->getTargetType()) {
			case OutputListNode::CC:
				addBeforeNote(juce::MidiMessage::controllerEvent(channel, node->getCCNumber(), node->getValue()));
				break;
			case OutputListNode::NOTE:
				addBeforeNote(juce::MidiMessage::noteOn(channel, node->getValue(), juce::uint8(64)));
				addAfterNote(juce::MidiMessage::noteOff(channel, node->getValue()));
				break;
			case OutputListNode::START:
				addStartDelay(node->getValue());
				break;
			case OutputListNode::END:
				addEndDelay(node->getValue());
				break;
			}
		}
	}
}

void NoteProcessor::addStartDelay(double delay)
{
	startDelaySamples += (delay / 1000) * sampleRate;
}

void NoteProcessor::addEndDelay(double delay)
{
	endDelaySamples += (delay / 1000) * sampleRate;
}

void NoteProcessor::addBeforeNote(juce::MidiMessage message)
{
	message.setChannel(channel);
	beforeNoteMessages.emplace_back(message);
}

void NoteProcessor::addAfterNote(juce::MidiMessage message)
{
	message.setChannel(channel);
	afterNoteMessages.emplace_back(message);
}

void NoteProcessor::applyStartDelay()
{
	target->startTime += startDelaySamples;
}

std::vector<juce::MidiMessage> NoteProcessor::getResults()
{
	target->endDelay += endDelaySamples;

	std::vector<juce::MidiMessage> results = std::vector<juce::MidiMessage>();

	for (const auto& message : beforeNoteMessages) {
		results.emplace_back(message);
	}

	results.emplace_back(juce::MidiMessage::noteOn(channel, target->pitch, (juce::uint8)target->velocity));

	for (const auto& message : afterNoteMessages) {
		results.emplace_back(message);
	}

	return results;
}