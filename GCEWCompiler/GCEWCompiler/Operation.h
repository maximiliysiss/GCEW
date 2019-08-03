#pragma once
#include "Tree.h"

namespace  gcew::trees::elements
{
	class Operation
		: public Element
	{
	public:
		Operation(int index, std::string line, RegexResult reg);
		virtual ~Operation();
		void toCode(std::string& code) = 0;
	};
}

