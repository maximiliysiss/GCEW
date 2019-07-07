#pragma once
#include "Tree.h"

namespace gcew::trees::structural
{
	class ElseTree :
		public Tree
	{
	public:
		ElseTree(int index, std::string line);
		~ElseTree();
	};
}

