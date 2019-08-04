#pragma once
#include "TreeRegularBuilder.h"
#include "Element.h"
#include "AssigmentOperation.h"
#include "BreakOperation.h"
#include "CallOperation.h"
#include "ContinueOperation.h"
#include "ElseTree.h"
#include "ForTree.h"
#include "IfTree.h"
#include "FunctionTree.h"
#include "PureAsmTree.h"
#include "ReturnOperation.h"
#include "WhileTree.h"

namespace gcew::trees::structural
{
	class CycleTree;
	class IfTree;
	class FunctionTree;
}

namespace gcew::trees
{
	using namespace gcew::trees::elements;
	using namespace gcew::regulars;
	using namespace gcew::trees::elements::operations;
	using namespace gcew::trees::structural;

	Element * construct_elements(RegexResult reg, int index, std::string line);
}

