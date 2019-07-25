#pragma once
#include "Tree.h"
#include "BaseNode.h"

namespace gcew::trees::structural
{
	using namespace gcew::trees::parser;

	class CycleTree :
		public Tree
	{
	protected:
		BaseNode * condition{ nullptr };
	public:
		CycleTree(int index, std::string line, gcew::commons::RegexResult reg);
		~CycleTree();
	};
}


