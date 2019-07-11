#include "Variable.h"

namespace gcew::trees::elements
{
	Variable::Variable(int index, std::string line)
		:Element(index, line, RegexResult::Type)
	{
		auto parts = splitter(line, ' ');
		type = parts[0];
		name = parts[1];
		if (line.find('=') != std::string::npos) {
			parts = splitter(line, '=');
			this->exp = Parser::preParser(trim(parts[1]).substr(0, parts[1].length() - 1));
		}
	}

	void Variable::toCode(std::string & code)
	{
	}

	void Variable::createInitializeData(std::string & code)
	{
		if (this->exp)
			exp->toCode(code);
	}

	void Variable::createData(std::string & code)
	{
		std::string value = "?";
		if (typeid(*this->exp) == typeid(Term))
			value = ((Term*)exp)->getValue();
		code += name + " " + gcew::commons::CompileConfiguration::typeOperation[type][Operations::Convert] + " " + value + "\n";
	}

	Variable::~Variable()
	{
		if (exp)
			delete exp;
	}
}
