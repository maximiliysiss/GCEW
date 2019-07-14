#pragma once
#ifndef INCLUDE_OPERATION_H
#define INCLUDE_OPERATION_H

#include "CompileConfiguration.h"
#include "Operation.h"
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
	};


}

#endif // !INCLUDE_OPERATION_H

