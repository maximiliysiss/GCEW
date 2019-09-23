#include "ForTree.h"

namespace gcew::trees::structural
{
	void ForTree::createData(std::string & code)
	{
		CycleTree::createData(code);
		if (startAction)
			this->startAction->createData(code);
		if (iteration)
			this->iteration->createData(code);
	}

	bool ForTree::isCallFunction(std::string name)
	{
		bool result = CycleTree::isCallFunction(name);
		if (startAction)
			result = result || startAction->isCallFunction(name);
		if (iteration)
			result = result || iteration->isCallFunction(name);
		return result;
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
		if (parts.size() > 1 && parts[1].length() > 1)
			this->condition = gcew::commons::Parser::preParser(parts[1].substr(0, parts[1].length() - 1));
		if (parts.size() > 2 && parts[2].length() > 1) {
			this->iteration = gcew::trees::construct_elements(gcew::regulars::TreeRegularBuilder::regex(parts[2]), 0, parts[2]);
			this->iteration->postWork(this);
		}
		if (this->startAction)
			this->startAction->postWork(this);
		Tree::postWork(tree);
	}

	bool ForTree::isInActiveTree(std::string name)
	{
		return CycleTree::isInActiveTree(name) || this->iteration->isInActiveTree(name)
			|| this->startAction->isInActiveTree(name);
	}

	ForTree::ForTree(int index, std::string & line)
		:CycleTree(index, line, RegexResult::For)
	{
		this->breakOperation = gcew::commons::CompileConfiguration::typeOperation["for"][gcew::commons::Operations::End] + name;
		this->continueOperation = gcew::commons::CompileConfiguration::typeOperation["for"][gcew::commons::Operations::Iter] + name;
		auto startBreak = line.find('(');
		auto endBreak = line.find(')');
		parts = gcew::commons::leftSplitter(line.substr(startBreak + 1, endBreak - startBreak - 1), ';');
		if (parts.size() > 0 && parts[0].length() > 1) {
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
		std::string start = gcew::commons::CompileConfiguration::typeOperation["for"][gcew::commons::Operations::Start] + name;
		std::string body = gcew::commons::CompileConfiguration::typeOperation["for"][gcew::commons::Operations::Body] + name;
		std::string iter = continueOperation;
		std::string end = breakOperation;
		if (startAction)
			startAction->toCode(code);
		code += start + ":\n";
		code += "finit\n";
		auto cond = dynamic_cast<BoolNode*>(condition)->toBoolCode(code);
		auto index = code.find(cond[1]);
		code.insert(index + cond[1].length(), "\njmp " + body + "\n");
		index = code.find(cond[2]);
		code.insert(index + cond[2].length(), "\njmp " + end + "\n");
		code += iter + ":\n";
		iteration->toCode(code);
		code += "jmp " + start + "\n";
		code += body + ":\n";
		Tree::toCode(code);
		code += "jmp " + iter + "\n";
		code += end + ":\n";
	}

}
