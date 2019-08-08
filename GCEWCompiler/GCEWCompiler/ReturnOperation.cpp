#include "ReturnOperation.h"



void gcew::trees::elements::operations::ReturnOperation::createData(std::string & code)
{
	if (ret)
		this->ret->createData(code);
}

gcew::trees::elements::operations::ReturnOperation::ReturnOperation(int index, std::string line)
	:Operation(index, line, RegexResult::Return)
{
	auto parts = gcew::commons::splitter(line.substr(0, line.length() - 1), ' ');
	if (parts.size() > 1)
		ret = gcew::commons::Parser::preParser(parts[1]);
}

gcew::trees::elements::operations::ReturnOperation::~ReturnOperation()
{
	if (functionTree)
		delete functionTree;
}

void gcew::trees::elements::operations::ReturnOperation::postWork(void * tree)
{
	functionTree = ((gcew::trees::structural::Tree*)tree)->findFunctionTreeUp();
	if (ret)
		ret->postWork(tree);
}

void gcew::trees::elements::operations::ReturnOperation::toCode(std::string & code)
{
	if (ret)
		ret->toCode(code);
	code += "jmp " + gcew::commons::CompileConfiguration::typeOperation["function"][gcew::commons::Operations::End] + functionTree->getName() + "\n";
}
