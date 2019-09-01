#include "Variable.h"

namespace gcew::trees::elements
{
	bool Variable::isCallFunction(std::string name)
	{
		if (this->exp)
			return this->exp->isCallFunction(name);
		return false;
	}
	void Variable::postWork(void * tree)
	{
		if (exp)
			exp->postWork(tree);
	}

	Variable::Variable(int index, std::string line)
		:Element(index, line, RegexResult::Type)
	{
		auto parts = splitter(line, ' ');
		bool breakOperation = line[line.length() - 1] == ';';
		type = parts[0];
		name = parts[1];
		codeName = name + gcew::commons::createUniqueGUID();
		if (line.find('=') != std::string::npos) {
			parts = splitter(line, '=');
			this->exp = Parser::preParser(trim(parts[1]).substr(0, parts[1].length() - breakOperation));
		}
		else
			name = name.substr(0, name.length() - breakOperation);
	}

	void Variable::toCode(std::string & code)
	{
		if (exp) {
			auto * term = dynamic_cast<Term*>(exp);
			if (!term || !term->isTempValue()) {
				exp->toCode(code);
				code += gcew::commons::CompileConfiguration::typeOperation[type][gcew::commons::Operations::FieldGet] + " " + codeName + "\n";
			}
		}
	}

	void Variable::createData(std::string & code)
	{
		std::string value = "?";
		auto * term = dynamic_cast<gcew::trees::parser::Term*>(this->exp);
		if (term && term->isTempValue())
			value = ((gcew::trees::parser::Term*)exp)->getValue();
		else if (exp)
			exp->createData(code);
		code += codeName + " " + gcew::commons::CompileConfiguration::typeOperation[type][Operations::Convert] + " " + value + "\n";
	}

	Variable::~Variable()
	{
		if (exp)
			delete exp;
	}
}
