#include "IfTree.h"

namespace gcew::trees::structural
{

	IfTree::IfTree(int index, std::string line)
		:Tree(index, line, gcew::commons::RegexResult::If)
	{
		auto bracketOpen = line.find('(');
		auto bracketClose = line.find(')');
		expression = gcew::commons::Parser::preParser(line.substr(bracketOpen + 1, bracketClose - bracketOpen - 1));
	}

	IfTree::~IfTree()
	{
	}

}
