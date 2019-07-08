#pragma once
#ifndef FORTREE_H
#define FORTREE_H
#include "CycleTree.h"
#include "ElementsContrustor.h"
#include "Parser.h"

namespace gcew::trees::structural
{
	class ForTree :
		public CycleTree
	{
		Element * iteration{ nullptr };
		Element * startAction{ nullptr };
	public:
		ForTree(int index, std::string & line);
		~ForTree();
	};
}

#endif // !FORTREE_H


