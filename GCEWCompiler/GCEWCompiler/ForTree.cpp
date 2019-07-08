#include "ForTree.h"

namespace gcew::trees::structural
{
	ForTree::ForTree(int index, std::string & line)
		:CycleTree(index, line, RegexResult::For)
	{
		auto startBreak = line.find('(');
		auto endBreak = line.find(')');
		auto parts = gcew::commons::leftSplitter(line.substr(startBreak + 1, endBreak - startBreak - 1), ';');
		if (parts[0].length() > 0) {
			gcew::regulars::RegexResult reg = gcew::regulars::TreeRegularBuilder::regex(parts[0]);
			this->startAction = gcew::trees::construct_elements(reg, 0, parts[0]);
		}
		if (parts[1].length() > 0)
			this->condition = gcew::commons::Parser::preParser(parts[1].substr(0, parts[1].length() - 1));
		if (parts[2].length() > 0)
			this->iteration = gcew::trees::construct_elements(gcew::regulars::TreeRegularBuilder::regex(parts[2]), 0, parts[2]);
	}

	ForTree::~ForTree()
	{
		if (iteration)
			delete iteration;
		if (startAction)
			delete startAction;
	}

}
