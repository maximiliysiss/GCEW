#include "Operation.h"

namespace gcew::trees::elements
{

	Operation::Operation(int index, std::string line, RegexResult reg)
		: Element(index, line, reg)
	{
	}

	Operation::~Operation()
	{
	}

}
