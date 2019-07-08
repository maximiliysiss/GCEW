#include "ReturnOperation.h"



gcew::trees::elements::operations::ReturnOperation::ReturnOperation(int index, std::string line)
	:Operation(index, line, RegexResult::Return)
{
}

gcew::trees::elements::operations::ReturnOperation::~ReturnOperation()
{
	if (functionTree)
		delete functionTree;
}
