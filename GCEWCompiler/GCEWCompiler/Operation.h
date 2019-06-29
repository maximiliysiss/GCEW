#pragma once
#ifndef OPERATION_H
#include "Element.h"

#define OPERATION_H

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


#endif // !OPERATION_H

