#pragma once
#include "NoteContext.h"

class IInputTreeNode {
public:
	virtual ~IInputTreeNode() = default;
	virtual NoteContext& visit(NoteContext& context) = 0;
	virtual void getTags(std::unordered_set<std::string>& tags) = 0;
};