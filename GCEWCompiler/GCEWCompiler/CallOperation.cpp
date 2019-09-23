#include "CallOperation.h"

void gcew::trees::elements::operations::CallOperation::createData(std::string & code)
{
	for (auto arg : arguments)
		arg->createData(code);
}

bool gcew::trees::elements::operations::CallOperation::isCallFunction(std::string name)
{
	return name == function->getFuncName();
}

void gcew::trees::elements::operations::CallOperation::postWork(void * tree)
{
	function = this->tree->findFunctionTree(name);
	for (auto arg : arguments)
		arg->postWork(tree);
}

gcew::trees::elements::operations::CallOperation::CallOperation(int index, std::string line)
	:Operation(index, line, RegexResult::Call)
{
	name = splitter(line, '(')[0];
	auto startBracket = line.find('(');
	auto endBracket = line.find_last_of(')');
	auto arg = getArguments(line.substr(startBracket + 1, endBracket - startBracket - 1));
	std::for_each(arg.begin(), arg.end(), [this](std::string& str) {
		str = trim(str);
		arguments.push_back(gcew::commons::Parser::preParser(str));
	});
}

bool gcew::trees::elements::operations::CallOperation::isInActiveTree(std::string name)
{
	auto result = false;
	for (auto arg : arguments)
		result = result || arg->isInActiveTree(name);
	return result;
}

gcew::trees::elements::operations::CallOperation::~CallOperation()
{
}

void gcew::trees::elements::operations::CallOperation::toCode(std::string & code)
{
	for (auto arg : arguments) {
		arg->toCode(code);
	}
	code += "call " + function->getName() + "\n";
}
