#pragma once
#ifndef IFTREE_H
#define IFTREE_H
#include "Tree.h"
#include "ElseTree.h"

namespace gcew::trees::structural
{
	class IfTree :
		public Tree
	{
		ElseTree * elseTree;
	public:
		IfTree(int index, std::string line);
		inline void setElse(ElseTree* elseTree) { this->elseTree = elseTree; }
		~IfTree();
	};
}

#endif // !IFTREE_H


