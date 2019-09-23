#pragma once
#ifndef ASSIGMENTOPERATION_H
#define ASSIGMENTOPERATION_H

#include "Parser.h"
#include "Operation.h"

namespace gcew::trees::elements::operations
{
	class AssigmentOperation :
		public Operation
	{
		Variable * var;
		BaseNode * exp;
		std::string name;
	public:
		virtual bool isCallFunction(std::string name) override;
		AssigmentOperation(int index, std::string line);
		~AssigmentOperation();

		// Inherited via Operation
		virtual void toCode(std::string & code) override;

		// Inherited via Operation
		virtual void postWork(void * tree) override;
		virtual bool isInActiveTree(std::string name) override;
		virtual void createData(std::string & code) override;
	};
}

#endif // !ASSIGMENTOPERATION_H


