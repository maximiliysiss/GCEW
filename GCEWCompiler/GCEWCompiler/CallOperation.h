#pragma once
#ifndef CALLOPERATION_H
#define CALLOPERATION_H

#include "Operation.h"

namespace gcew::trees::elements::operations
{
	class CallOperation :
		public Operation
	{
	public:
		CallOperation(int index, std::string line);
		~CallOperation();

		// Inherited via Operation
		virtual void toCode(std::string & code) override;

		// Inherited via Operation
		virtual void postTreeWork(gcew::trees::structural::Tree * tree) override;
	};
}

#endif // !CALLOPERATION_H


