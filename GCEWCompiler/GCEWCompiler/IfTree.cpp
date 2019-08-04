#include "IfTree.h"

namespace gcew::trees::structural
{
	void IfTree::createData(std::string & code)
	{
		Tree::createData(code);
		this->expression->createData(code);
	}

	void IfTree::toCode(std::string & code)
	{
		std::string start = gcew::commons::CompileConfiguration::typeOperation["if"][gcew::commons::Operations::Start] + name;
		std::string end = gcew::commons::CompileConfiguration::typeOperation["if"][gcew::commons::Operations::End] + name;
		code += "finit\n";
		auto cond = dynamic_cast<gcew::trees::parser::BoolNode*>(expression)->toBoolCode(code);
		auto index = code.find(cond[1]);
		code.insert(index + cond[1].length(), "\njmp " + start + "\n");
		index = code.find(cond[2]);
		if (elseTree)
			code.insert(index + cond[2].length(), "\njmp " + gcew::commons::CompileConfiguration::typeOperation["else"][gcew::commons::Operations::Start] + elseTree->getName() + "\n");
		else
			code.insert(index + cond[2].length(), "\njmp " + end + "\n");
		code += start + ":\n";
		Tree::toCode(code);
		code += "jmp " + end + "\n";
		if (elseTree)
			elseTree->toElseCode(code);
		code += end + ":\n";
	}

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
