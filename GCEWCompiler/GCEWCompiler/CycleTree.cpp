#include "CycleTree.h"


namespace gcew::trees::structural
{
	CycleTree::CycleTree(int index, std::string line, RegexResult reg)
		:Tree(index, line, reg)
	{
	}

	CycleTree::~CycleTree()
	{
		if (condition)
			delete condition;
	}
}
