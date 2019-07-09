#pragma once
#ifndef BREAKOPERATION_H
#define BREAKOPERATION_H

#include "Operation.h"
#include "CycleTree.h"

namespace gcew::trees::elements::operations
{
	class BreakOperation :
		public Operation
	{
		gcew::trees::structural::CycleTree * cycleTree;
	public:
		BreakOperation(int index, std::string line);

		inline void setCycleTree(gcew::trees::structural::CycleTree * cycleTree) { this->cycleTree = cycleTree; }

		// Inherited via Operation
		virtual void toCode(std::string & code) override;
	};
}


#endif // !BREAKOPERATION_H


