#include "AssigmentOperation.h"

gcew::trees::elements::operations::AssigmentOperation::AssigmentOperation(int index, std::string line)
	:Operation(index, line, gcew::commons::RegexResult::Assigment)
{
	exp = Parser::preParser(line.substr(line.find('=') + 1));
}

gcew::trees::elements::operations::AssigmentOperation::~AssigmentOperation()
{
	if (exp)
		delete exp;
}

void gcew::trees::elements::operations::AssigmentOperation::toCode(std::string & code)
{
}

void gcew::trees::elements::operations::AssigmentOperation::postTreeWork(gcew::trees::structural::Tree * tree)
{
}
