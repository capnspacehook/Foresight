#pragma once

#include "JuceHeader.h"
#include "IInputTreeNode.h"
#include "InputTreeCase.h"

class InputTreeRootNode : public IInputTreeNode {
public:
	explicit InputTreeRootNode(const juce::XmlElement& source);
	NoteContext& visit(NoteContext& context) override;
	void getTags(std::unordered_set<std::string>& tags) override;
private:
	std::vector<std::unique_ptr<IInputTreeNode>> children;
};