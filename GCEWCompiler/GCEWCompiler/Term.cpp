#include "Term.h"


namespace gcew::trees::parser
{
	Term::Term(std::string value)
		:value(value)
	{
		if (gcew::commons::isNumber(this->value)) {
			this->type = gcew::commons::CompileConfiguration::getTypeInitializeByValue(this->value);
			this->isTemp = true;
			this->name = gcew::commons::createUniqueGUID();
		}
		else {
			auto var = gcew::commons::CompileConfiguration::currentTree->findVariableByName(value);
			this->type = var->getType();
			this->name = value;
		}
	}

	Term::~Term()
	{
	}

	void Term::createData(std::string & code)
	{
		if (isTemp)
			code += name + " " + gcew::commons::CompileConfiguration::typeOperation[type][Operations::Convert] + " " + value + "\n";
	}

	void Term::toCode(std::string & code)
	{
		code += gcew::commons::CompileConfiguration::typeOperation[type][Operations::FieldSet] + " " + name + "\n";
	}

}
