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
		virtual void postTreeWork(gcew::trees::structural::Tree* tree) {}
	};
}

