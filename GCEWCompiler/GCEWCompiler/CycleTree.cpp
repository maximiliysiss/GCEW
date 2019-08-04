#include "CycleTree.h"


namespace gcew::trees::structural
{
	void CycleTree::createData(std::string & code)
	{
		Tree::createData(code);
		if (condition)
			condition->createData(code);
	}

	CycleTree::CycleTree(int index, std::string line, gcew::commons::RegexResult reg)
		:Tree(index, line, reg)
	{
	}

	CycleTree::~CycleTree()
	{
		if (condition)
			delete condition;
	}
}
