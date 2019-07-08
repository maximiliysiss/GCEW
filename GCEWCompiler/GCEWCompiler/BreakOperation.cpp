#include "BreakOperation.h"

gcew::trees::elements::operations::BreakOperation::BreakOperation(int index, std::string line)
	:Operation(index, line, RegexResult::Break)
{
}

void gcew::trees::elements::operations::BreakOperation::toCode(std::string & code)
{
}

void gcew::trees::elements::operations::BreakOperation::postTreeWork(gcew::trees::structural::Tree * tree)
{
}
