#include "ElseTree.h"

namespace gcew::trees::structural
{

	ElseTree::ElseTree(int index, std::string line)
		:Tree(index, line, RegexResult::Else)
	{
	}


	ElseTree::~ElseTree()
	{
	}

}
