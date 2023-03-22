#include "InputTreeRootNode.h"
#include "InputTreeNodeFactory.h"

InputTreeRootNode::InputTreeRootNode(const juce::XmlElement& source)
{
    for (const auto& childElement : source.getChildIterator()) {
        IInputTreeNode* child = InputTreeNodeFactory::make(*childElement);
        children.emplace_back(child);
    }
}

NoteContext& InputTreeRootNode::visit(NoteContext& context)
{
    for (const auto& child : children) {
        child->visit(context);
    }

    return context;
}

void InputTreeRootNode::getTags(std::unordered_set<std::string>& tags)
{
    for (const auto& child : children) {
        child->getTags(tags);
    }
}