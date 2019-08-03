#include "ForTree.h"

namespace gcew::trees::structural
{
	void ForTree::createData(std::string & code)
	{
		Tree::createData(code);
		this->startAction->createData(code);
		this->condition->createData(code);
		this->iteration->createData(code);
	}
	gcew::trees::elements::Variable * ForTree::findVariableByName(std::string name)
	{
		auto * var = dynamic_cast<Variable*>(startAction);
		if (var && var->getName() == name)
			return var;
		return Tree::findVariableByName(name);
	}

	void ForTree::postWork(void * tree)
	{
		auto * tr = dynamic_cast<Tree*>(this);
		Tree::currentTree = &tr;
		if (parts.size() > 1 && parts[1].length() > 0)
			this->condition = gcew::commons::Parser::preParser(parts[1].substr(0, parts[1].length() - 1));
		if (parts.size() > 2 && parts[2].length() > 0) {
			this->iteration = gcew::trees::construct_elements(gcew::regulars::TreeRegularBuilder::regex(parts[2]), 0, parts[2]);
			this->iteration->postWork(this);
		}
		if (this->startAction)
			this->startAction->postWork(this);
	}

	ForTree::ForTree(int index, std::string & line)
		:CycleTree(index, line, RegexResult::For)
	{
		auto startBreak = line.find('(');
		auto endBreak = line.find(')');
		parts = gcew::commons::leftSplitter(line.substr(startBreak + 1, endBreak - startBreak - 1), ';');
		if (parts.size() > 0 && parts[0].length() > 0) {
			gcew::regulars::RegexResult reg = gcew::regulars::TreeRegularBuilder::regex(parts[0]);
			this->startAction = gcew::trees::construct_elements(reg, 0, parts[0]);
		}
	}

	ForTree::~ForTree()
	{
		if (iteration)
			delete iteration;
		if (startAction)
			delete startAction;
	}

	void ForTree::toCode(std::string & code)
	{
	}

}
