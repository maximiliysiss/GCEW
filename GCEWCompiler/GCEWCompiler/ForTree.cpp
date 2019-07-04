#include "ForTree.h"

namespace gcew::trees::structural
{
	ForTree::ForTree(int index, std::string & line)
		:CycleTree(index, line, RegexResult::For)
	{
		auto startBreak = line.find('(');
		auto endBreak = line.find(')');
		auto parts = gcew::commons::splitter(line.substr(startBreak + 1, endBreak - startBreak - 1), ';');
	}

	ForTree::~ForTree()
	{
		if (iteration)
			delete iteration;
		if (startAction)
			delete startAction;
	}

}
