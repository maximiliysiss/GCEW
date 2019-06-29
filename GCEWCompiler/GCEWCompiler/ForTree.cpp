#include "ForTree.h"

namespace gcew::trees::structural
{
	ForTree::ForTree(int index, std::string & line)
		:CycleTree(index, line, RegexResult::For)
	{
	}

	ForTree::~ForTree()
	{
		if (iteration)
			delete iteration;
		if (startAction)
			delete startAction;
	}

}
