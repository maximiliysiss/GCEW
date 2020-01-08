#pragma once
#include "Operation.h"
#include "FunctionTree.h"

namespace gcew::trees::elements::operations
{
	class CallOperation :
		public Operation
	{
		std::string name;
		gcew::trees::structural::FunctionTree * function{ nullptr };
		std::vector<gcew::trees::parser::BaseNode*> arguments;
		virtual void createData(std::string & code);
		gcew::trees::structural::Tree * tree;
	public:
		virtual bool isCallFunction(std::string name) override;
		inline void setTree(gcew::trees::structural::Tree * tree) { this->tree = tree; }
		inline std::string getFunctionName() { return function->getFuncName(); }
		inline std::string getOutputType() { return function->getFuncOutputType(); }
		virtual void postWork(void* tree);
		CallOperation(int index, std::string line);
		virtual bool isInActiveTree(std::string name) override;
		~CallOperation();

		// Inherited via Operation
		virtual void toCode(std::string & code) override;
	};
}


