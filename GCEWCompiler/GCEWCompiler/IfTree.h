#pragma once
#include "Tree.h"
#include "ElseTree.h"
#include "Parser.h"

namespace gcew::trees::structural
{
	class IfTree :
		public Tree
	{
		gcew::trees::parser::BaseNode * expression;
		ElseTree * elseTree;
	public:
		IfTree(int index, std::string line);
		inline void setElse(ElseTree* elseTree) { this->elseTree = elseTree; }
		~IfTree();
	};
}


