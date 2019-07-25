#include "ElseTree.h"

namespace gcew::trees::structural
{

	ElseTree::ElseTree(int index, std::string line)
		:Tree(index, line, gcew::commons::RegexResult::Else)
	{
	}


	ElseTree::~ElseTree()
	{
	}

}
