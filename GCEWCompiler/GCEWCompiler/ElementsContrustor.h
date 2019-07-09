#pragma once
#include "TreeRegularBuilder.h"
#include "Element.h"
#include "Variable.h"
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

namespace gcew::trees
{
	using namespace gcew::trees::elements;
	using namespace gcew::regulars;
	using namespace gcew::trees::elements::operations;
	using namespace gcew::trees::structural;

	Element * construct_elements(RegexResult reg, int index, std::string line);
}
