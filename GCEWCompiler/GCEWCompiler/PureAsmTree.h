#pragma once
#include "Tree.h"

namespace gcew::trees::structural
{
	class PureAsmTree :
		public Tree
	{
	public:
		PureAsmTree(int index, std::string line);
	};

}
