#pragma once

#include "CompileConfiguration.h"
#include "BaseNode.h"
#include "Instruments.h"
#include "Tree.h"

namespace gcew::trees::parser
{
	class Term :
		public BaseNode
	{
	protected:
		bool isTemp{ false };
		std::string value;
		std::string type;
	public:
		inline std::string getValue() const { return value; }
		Term(std::string value, std::string type);
		~Term();
		virtual void createData(std::string & code) override;
		// Inherited via BaseNode
		virtual void toCode(std::string & code) override;
	};
}


