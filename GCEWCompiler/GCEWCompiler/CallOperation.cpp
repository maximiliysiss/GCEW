#include "CallOperation.h"

void gcew::trees::elements::operations::CallOperation::createData(std::string & code)
{
	for (auto arg : arguments)
		arg->createData(code);
}

void gcew::trees::elements::operations::CallOperation::postWork(void * tree)
{
	function = ((gcew::trees::structural::Tree*)tree)->findFunctionTree(name);
	for (auto arg : arguments)
		arg->postWork(tree);
}

gcew::trees::elements::operations::CallOperation::CallOperation(int index, std::string line)
	:Operation(index, line, RegexResult::Call)
{
	name = splitter(line, '(')[0];
	auto startBracket = line.find('(');
	auto endBracket = line.find(')');
	auto arg = splitter(line.substr(startBracket + 1, endBracket - startBracket - 1), ',');
	std::for_each(arg.begin(), arg.end(), [this](std::string& str) {
		str = trim(str);
		arguments.push_back(gcew::commons::Parser::preParser(str));
	});
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
