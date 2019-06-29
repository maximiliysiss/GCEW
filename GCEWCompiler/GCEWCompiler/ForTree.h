#pragma once
#ifndef FORTREE_H
#define FORTREE_H
#include "CycleTree.h"

namespace gcew::trees::structural
{
	class ForTree :
		public CycleTree
	{
		BaseNode * iteration{ nullptr };
		BaseNode * startAction{ nullptr };
	public:
		ForTree(int index, std::string & line);
		~ForTree();
	};
}

#endif // !FORTREE_H


