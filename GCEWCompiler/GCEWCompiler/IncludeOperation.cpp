#include "IncludeOperation.h"

namespace gcew::trees::elements::operations
{

	IncludeOperation::IncludeOperation(int index, std::string line)
		: Operation(index, line, RegexResult::Include)
	{
		auto openBreak = line.find("<");
		auto closeBreak = line.find(">");

		fileName = line.substr(openBreak + 1, closeBreak - openBreak - 1);
		if (fileName.find(".") != std::string::npos) {
			isLocal = true;
			fileName = CompileConfiguration::instance().workPath + fileName;
		}
		else
			fileName = CompileConfiguration::instance().getLibsPath() + fileName;
	}


	IncludeOperation::~IncludeOperation()
	{
	}

	void IncludeOperation::toCode(std::string & code)
	{
	}

}
