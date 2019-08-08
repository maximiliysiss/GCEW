#pragma once
#include "Operation.h"
#include "FunctionTree.h"

namespace gcew::trees::elements::operations
{
	class ReturnOperation :
		public Operation
	{
		gcew::trees::structural::FunctionTree * functionTree;
		gcew::trees::elements::BaseNode * ret;
		virtual void createData(std::string & code);
	public:
		ReturnOperation(int index, std::string line);
		inline void setFunctionTree(gcew::trees::structural::FunctionTree * functionTree) { this->functionTree = functionTree; }
		~ReturnOperation();
		virtual void postWork(void * tree) override;
		// Inherited via Operation
		virtual void toCode(std::string & code) override;
	};
}

