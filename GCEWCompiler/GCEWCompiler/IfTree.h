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
		virtual void postWork(void * tree);
	public:
		virtual bool isCallFunction(std::string name) override;
		virtual void toCode(std::string & code) override;
		IfTree(int index, std::string line);
		virtual bool isInActiveTree(std::string name) override;
		inline void setElse(ElseTree* elseTree) { this->elseTree = elseTree; }
		~IfTree();
	};
}


