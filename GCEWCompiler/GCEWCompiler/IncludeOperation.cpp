#include "IncludeOperation.h"

namespace gcew::trees::elements::operations
{

	IncludeOperation::IncludeOperation(int index, std::string line)
		: Operation(index, line, RegexResult::Include)
	{
		auto parts = splitter(line.substr(0, line.length() - 1), ' ');

		fileName = parts[1];
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
