#include "ContinueOperation.h"


gcew::trees::elements::operations::ContinueOperation::ContinueOperation(int index, std::string line, gcew::trees::structural::CycleTree * cycleTree)
	:Operation(index, line, RegexResult::Continue), cycleTree(cycleTree)
{
}

gcew::trees::elements::operations::ContinueOperation::~ContinueOperation()
{
}

void gcew::trees::elements::operations::ContinueOperation::toCode(std::string & code)
{
}

void gcew::trees::elements::operations::ContinueOperation::postTreeWork(gcew::trees::structural::Tree * tree)
{
}
