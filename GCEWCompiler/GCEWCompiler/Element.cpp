#include "Element.h"

namespace gcew::trees::elements
{
	Element::Element(int index, std::string line)
		:line(line), index(index), nodeType(RegexResult::NotClassic)
	{
	}

	Element::Element(int index, std::string line, RegexResult reg)
		: line(line), index(index), nodeType(reg)
	{
	}


	Element::~Element()
	{
	}
}
