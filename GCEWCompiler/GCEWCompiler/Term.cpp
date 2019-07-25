#include "Term.h"


namespace gcew::trees::parser
{
	Term::Term(std::string value, std::string type)
		:value(value)
	{
		if (gcew::commons::isNumber(this->value)) {
			this->type = gcew::commons::CompileConfiguration::getTypeInitializeByValue(this->value);
			this->isTemp = true;
			this->name = gcew::commons::createUniqueGUID();
		}
		else {
			auto var = (*gcew::trees::structural::Tree::currentTree)->findVariableByName(value);
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
			code += name + " " + gcew::commons::CompileConfiguration::typeOperation[type][gcew::commons::Operations::Convert] + " " + value + "\n";
	}

	void Term::toCode(std::string & code)
	{
		code += gcew::commons::CompileConfiguration::typeOperation[type][gcew::commons::Operations::FieldSet] + " " + name + "\n";
	}

}
