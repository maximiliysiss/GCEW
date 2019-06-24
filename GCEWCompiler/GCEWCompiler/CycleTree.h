#pragma once
#ifndef CYCLETREE_H
#define CYCLETREE_H

#include "Tree.h"

namespace gcew::trees::structural
{
	class CycleTree :
		public Tree
	{
	public:
		CycleTree(int index, std::string line, RegexResult reg);
		~CycleTree();
	};
}

#endif // !CYCLETREE_H


