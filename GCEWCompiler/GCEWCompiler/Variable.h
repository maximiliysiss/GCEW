#pragma once
#ifndef VARIABLE_H
#include "Element.h"
#include "BaseNode.h"
#include "Parser.h"
#include "Instruments.h"

#define VARIABLE_H

namespace  gcew::trees::elements
{
	class Variable
		:public Element
	{
	protected:
		std::string name;
		std::string type;
		gcew::trees::parser::BaseNode * exp;
	public:
		inline std::string getName() const { return name; }
		Variable(int index, std::string line);
		void toCode(std::string & code);
		~Variable();
	};
}

#endif // !VARIABLE_H


