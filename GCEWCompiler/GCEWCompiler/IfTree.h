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
		virtual void createData(std::string & code);
	public:
		virtual void toCode(std::string & code) override;
		IfTree(int index, std::string line);
		inline void setElse(ElseTree* elseTree) { this->elseTree = elseTree; }
		~IfTree();
	};
}


