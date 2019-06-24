#include "Variable.h"

namespace gcew::trees::elements
{
	Variable::Variable(int index, std::string line)
		:Element(index, line, RegexResult::Type)
	{
	}

	Variable::~Variable()
	{
	}
}
