#include "AssigmentOperation.h"

bool gcew::trees::elements::operations::AssigmentOperation::isCallFunction(std::string name)
{
	return this->exp->isCallFunction(name);
}

gcew::trees::elements::operations::AssigmentOperation::AssigmentOperation(int index, std::string line)
	:Operation(index, line, gcew::commons::RegexResult::Assigment)
{
	line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
	auto equalPoz = line.find('=');
	bool isEnd = line.find(';') != std::string::npos;
	exp = Parser::preParser(line.substr(equalPoz + 1, line.length() - equalPoz - isEnd * 2));
	name = line.substr(0, equalPoz);
}

gcew::trees::elements::operations::AssigmentOperation::~AssigmentOperation()
{
	if (exp)
		delete exp;
}

void gcew::trees::elements::operations::AssigmentOperation::toCode(std::string & code)
{
	exp->toCode(code);
	code += gcew::commons::CompileConfiguration::typeOperation[var->getType()][gcew::commons::Operations::FieldGet]
		+ " " + var->getCodeName() + "\n";
}

void gcew::trees::elements::operations::AssigmentOperation::postWork(void * tree)
{
	this->var = ((gcew::trees::structural::Tree*)tree)->findVariableByName(name);
	this->exp->postWork(tree);
}

bool gcew::trees::elements::operations::AssigmentOperation::isInActiveTree(std::string name)
{
	return this->exp->isInActiveTree(name);
}

void gcew::trees::elements::operations::AssigmentOperation::createData(std::string & code)
{
	this->exp->createData(code);
}
