#include "IfTree.h"

namespace gcew::trees::structural
{

	IfTree::IfTree(int index, std::string line)
		:Tree(index, line, RegexResult::If)
	{
	}

	IfTree::~IfTree()
	{
	}

}
