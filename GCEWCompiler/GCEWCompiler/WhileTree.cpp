#include "WhileTree.h"

gcew::trees::structural::WhileTree::WhileTree(int index, std::string line)
	:CycleTree(index, line, gcew::commons::RegexResult::While)
{
	this->breakOperation = gcew::commons::CompileConfiguration::typeOperation["while"][gcew::commons::Operations::End] + name;
	this->continueOperation = gcew::commons::CompileConfiguration::typeOperation["while"][gcew::commons::Operations::Start] + name;
	auto startBrk = line.find('(');
	auto endBrk = line.find(')');
	this->condition = gcew::commons::Parser::preParser(line.substr(startBrk + 1, endBrk - startBrk - 1));
}

void gcew::trees::structural::WhileTree::toCode(std::string & code)
{
	std::string start = continueOperation;
	std::string body = gcew::commons::CompileConfiguration::typeOperation["while"][gcew::commons::Operations::Body] + name;
	std::string end = breakOperation;
	code += start + ":\n";
	code += "finit\n";
	auto cond = dynamic_cast<BoolNode*>(condition)->toBoolCode(code);
	auto index = code.find(cond[1]);
	code.insert(index + cond[1].length(), "\njmp " + body + "\n");
	index = code.find(cond[2]);
	code.insert(index + cond[2].length(), "\njmp " + end + "\n");
	code += body + ":\n";
	Tree::toCode(code);
	code += "jmp " + start + "\n";
	code += end + ":\n";
}
