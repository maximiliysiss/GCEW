#pragma once
#include "Operation.h"
#include "FunctionTree.h"

namespace gcew::trees::elements::operations
{
	class CallOperation :
		public Operation
	{
		std::string name;
		gcew::trees::structural::FunctionTree * function;
		std::vector<gcew::trees::parser::BaseNode*> arguments;
		virtual void createData(std::string & code);
	public:
		virtual void postWork(void* tree);
		CallOperation(int index, std::string line);
		~CallOperation();

		// Inherited via Operation
		virtual void toCode(std::string & code) override;
	};
}


