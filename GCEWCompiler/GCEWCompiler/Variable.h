#pragma once
#ifndef VARIABLE_H
#include "Element.h"


#define VARIABLE_H

namespace  gcew::trees::elements
{
	class Variable
		:public Element
	{
	public:
		Variable(int index, std::string line);
		void toCode(std::string & code);
		~Variable();
	};
}

#endif // !VARIABLE_H


