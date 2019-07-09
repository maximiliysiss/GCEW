#pragma once
#ifndef ASSIGMENTOPERATION_H
#define ASSIGMENTOPERATION_H

#include "Parser.h"
#include "Operation.h"
#include "Variable.h"

namespace gcew::trees::elements::operations
{
	class AssigmentOperation :
		public Operation
	{
		Variable * var;
		BaseNode * exp;
		std::string name;
	public:
		AssigmentOperation(int index, std::string line);
		~AssigmentOperation();

		// Inherited via Operation
		virtual void toCode(std::string & code) override;

		// Inherited via Operation
		virtual void postTreeWork(gcew::trees::structural::Tree * tree) override;
	};
}

#endif // !ASSIGMENTOPERATION_H


