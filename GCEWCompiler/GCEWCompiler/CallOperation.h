#pragma once
#ifndef CALLOPERATION_H
#define CALLOPERATION_H

#include "Operation.h"

namespace gcew::trees::elements::operations
{
	class CallOperation :
		public Operation
	{
		std::vector<std::string> arguments;
	public:
		CallOperation(int index, std::string line);
		~CallOperation();

		// Inherited via Operation
		virtual void toCode(std::string & code) override;
	};
}

#endif // !CALLOPERATION_H


