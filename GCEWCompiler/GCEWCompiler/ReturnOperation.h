#pragma once
#include "Operation.h"
#include "FunctionTree.h"

namespace gcew::trees::elements::operations
{
	class ReturnOperation :
		public Operation
	{
		gcew::trees::structural::FunctionTree * functionTree;
	public:
		ReturnOperation(int index, std::string line);
		inline void setFunctionTree(gcew::trees::structural::FunctionTree * functionTree) { this->functionTree = functionTree; }
		~ReturnOperation();

		// Inherited via Operation
		virtual void toCode(std::string & code) override;
		virtual void postTreeWork(gcew::trees::structural::Tree * tree) override;
	};
}

