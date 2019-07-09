#pragma once
#ifndef CONTINUEOPERATION_H
#define CONTINUEOPERATION_H

#include "Operation.h"
#include "CycleTree.h"

namespace gcew::trees::elements::operations
{
	class ContinueOperation :
		public Operation
	{
		gcew::trees::structural::CycleTree * cycleTree;
	public:
		ContinueOperation(int index, std::string line);
		~ContinueOperation();

		inline void setCycleTree(gcew::trees::structural::CycleTree * cycleTree) {
			this->cycleTree = cycleTree;
		}

		// Inherited via Operation
		virtual void toCode(std::string & code) override;
	};
}

#endif // !CONTINUEOPERATION_H


