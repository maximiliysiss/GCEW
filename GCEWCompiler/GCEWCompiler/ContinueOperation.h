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
		ContinueOperation(int index, std::string line, gcew::trees::structural::CycleTree * cycleTree);
		~ContinueOperation();

		// Inherited via Operation
		virtual void toCode(std::string & code) override;

		// Inherited via Operation
		virtual void postTreeWork(gcew::trees::structural::Tree * tree) override;
	};
}

#endif // !CONTINUEOPERATION_H


