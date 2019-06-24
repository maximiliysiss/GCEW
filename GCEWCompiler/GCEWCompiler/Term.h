#pragma once
#ifndef TERM_H
#define TERM_H

#include "BaseNode.h"

namespace gcew::parser
{
	class Term :
		public BaseNode
	{
	private:
		std::string value;
	public:
		Term(std::string value);
		~Term();
	};
}

#endif // !TERM_H


