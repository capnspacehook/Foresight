#include "InputTreeTagNode.h"

InputTreeTagNode::InputTreeTagNode(const juce::XmlElement& source)
{
	tag = source.getText().trim().toStdString();
}

NoteContext& InputTreeTagNode::visit(NoteContext& context)
{
	context.addTag(tag);
	return context;
}

void InputTreeTagNode::getTags(std::unordered_set<std::string>& tags)
{
	tags.emplace(tag);
}
