#include "Variable.h"

namespace gcew::trees::elements
{
	Variable::Variable(int index, std::string line)
		:Element(index, line, RegexResult::Type)
	{
		auto parts = splitter(line, ' ');
		bool end = line[line.length()] == ';';
		type = parts[0];
		name = parts[1];
		if (line.find('=') != std::string::npos) {
			parts = splitter(line, '=');
			this->exp = Parser::preParser(trim(parts[1]).substr(0, parts[1].length() - end));
		}
		else
			name = name.substr(0, name.length() - end);
	}

	void Variable::toCode(std::string & code)
	{
	}

	void Variable::createInitializeData(std::string & code)
	{
		if (this->exp && typeid(*this->exp) != typeid(gcew::trees::parser::Term)) {
			exp->toCode(code);
			code += gcew::commons::CompileConfiguration::typeOperation[type][gcew::commons::Operations::FieldGet] + " " + name + "\n";
		}
	}

	void Variable::createData(std::string & code)
	{
		std::string value = "?";
		if (exp && typeid(*this->exp) == typeid(gcew::trees::parser::Term))
			value = ((gcew::trees::parser::Term*)exp)->getValue();
		else if (exp)
			exp->createData(code);
		code += name + " " + gcew::commons::CompileConfiguration::typeOperation[type][Operations::Convert] + " " + value + "\n";
	}

	Variable::~Variable()
	{
		if (exp)
			delete exp;
	}
}
