#pragma once
#ifndef INCLUDE_OPERATION_H
#define INCLUDE_OPERATION_H


#include "Operation.h"
#include "CompileConfiguration.h"
#include "Instruments.h"

namespace gcew::trees::elements::operations
{
	class IncludeOperation :
		public Operation
	{
		std::string fileName;
		bool isLocal{ false };
	public:
		inline bool isLocalFile() const { return isLocal; }
		inline std::string getFileName() const { return fileName; }

		IncludeOperation(int index, std::string line);
		~IncludeOperation();

		// Inherited via Operation
		virtual void toCode(std::string & code) override;

		// Inherited via Operation
		virtual void postTreeWork(gcew::trees::structural::Tree * tree) override;
	};


}

#endif // !INCLUDE_OPERATION_H

