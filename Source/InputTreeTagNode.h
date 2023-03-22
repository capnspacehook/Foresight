#pragma once

#include "JuceHeader.h"
#include "IInputTreeNode.h"

class InputTreeTagNode : public IInputTreeNode {
public:
	explicit InputTreeTagNode(const juce::XmlElement& source);
	NoteContext& visit(NoteContext& context) override;
	void getTags(std::unordered_set<std::string>& tags) override;
private:
	std::string tag;
};