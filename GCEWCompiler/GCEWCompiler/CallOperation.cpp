#include "CallOperation.h"

gcew::trees::elements::operations::CallOperation::CallOperation(int index, std::string line)
	:Operation(index, line, RegexResult::Call)
{
}

gcew::trees::elements::operations::CallOperation::~CallOperation()
{
}

void gcew::trees::elements::operations::CallOperation::toCode(std::string & code)
{
}

void gcew::trees::elements::operations::CallOperation::postTreeWork(gcew::trees::structural::Tree * tree)
{
}
