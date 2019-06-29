#pragma once
#ifndef IFTREE_H
#define IFTREE_H
#include "Tree.h"

namespace gcew::trees::structural
{
	class IfTree :
		public Tree
	{
	public:
		IfTree(int index, std::string line);
		~IfTree();
	};
}

#endif // !IFTREE_H


