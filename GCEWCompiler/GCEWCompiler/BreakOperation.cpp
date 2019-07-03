#include "BreakOperation.h"

gcew::trees::elements::operations::BreakOperation::BreakOperation(int index, std::string line, gcew::trees::structural::CycleTree * cycleTree)
	:Operation(index, line, RegexResult::Break), cycleTree(cycleTree)
{
}

void gcew::trees::elements::operations::BreakOperation::toCode(std::string & code)
{
}

void gcew::trees::elements::operations::BreakOperation::postTreeWork(gcew::trees::structural::Tree * tree)
{
}
