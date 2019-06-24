#pragma once
#ifndef OPERATION_H
#include "Element.h"

#define OPERATION_H

namespace gcew::elements
{

	class Operation
		: public Element
	{
	public:
		Operation(int index, std::string line, RegexResult reg);
		virtual ~Operation();
	};
}


#endif // !OPERATION_H

