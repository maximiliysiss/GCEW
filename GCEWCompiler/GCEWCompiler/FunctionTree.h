#pragma once
#include "Tree.h"

namespace gcew::trees::structural
{
	class FunctionTree :
		public Tree
	{
		std::string name;
		std::string outputType;
		std::vector<std::string> arguments;
	public:
		FunctionTree(int index, std::string line, gcew::regulars::RegexResult reg);
	};
}

