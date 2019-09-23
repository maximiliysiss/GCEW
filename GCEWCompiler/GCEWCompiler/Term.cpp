#include "Term.h"


namespace gcew::trees::parser
{
	Term::Term(std::string value, std::string type)
		:value(value), BoolNode("")
	{
		if (gcew::commons::isNumber(this->value)) {
			this->type = gcew::commons::CompileConfiguration::getTypeInitializeByValue(this->value);
			this->isTemp = true;
			this->name = gcew::commons::createUniqueGUID();
		}
		else {
			auto var = (*gcew::trees::structural::Tree::currentTree)->findVariableByName(value);
			this->type = var->getType();
			this->name = var->getCodeName();
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

	std::vector<std::string> Term::toBoolCode(std::string & code)
	{
		toCode(code);
		return { name };
	}

	bool Term::isCallFunction(std::string name)
	{
		return false;
	}

}
