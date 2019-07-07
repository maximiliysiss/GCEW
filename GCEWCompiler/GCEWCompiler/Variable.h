#pragma once
#include "Element.h"
#include "Parser.h"

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


