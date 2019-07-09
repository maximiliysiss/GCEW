#include "CallOperation.h"

gcew::trees::elements::operations::CallOperation::CallOperation(int index, std::string line)
	:Operation(index, line, RegexResult::Call)
{
	auto startBracket = line.find('(');
	auto endBracket = line.find(')');
	arguments = splitter(line.substr(startBracket + 1, endBracket - startBracket - 1), ',');
}

gcew::trees::elements::operations::CallOperation::~CallOperation()
{
}

void gcew::trees::elements::operations::CallOperation::toCode(std::string & code)
{
}
