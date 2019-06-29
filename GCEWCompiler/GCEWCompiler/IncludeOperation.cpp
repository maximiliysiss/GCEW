#include "IncludeOperation.h"

namespace gcew::trees::elements::operations
{

	IncludeOperation::IncludeOperation(int index, std::string line)
		: Operation(index, line, RegexResult::Include)
	{
		auto openBreak = line.find("<");
		auto closeBreak = line.find(">");

		fileName = line.substr(openBreak + 1, closeBreak - openBreak - 1);
		if (fileName.find(".") != std::string::npos)
			isLocal = true;
	}


	IncludeOperation::~IncludeOperation()
	{
	}

	void IncludeOperation::toCode(std::string & code)
	{
	}

}
