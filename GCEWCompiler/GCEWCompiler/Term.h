#pragma once

#include "CompileConfiguration.h"
#include "BaseNode.h"
#include "Instruments.h"
#include "Tree.h"

namespace gcew::trees::parser
{
	class Term :
		public BaseNode, public BoolNode
	{
	protected:
		bool isTemp{ false };
		std::string value;
		std::string type;
	public:
		inline bool isTempValue() const { return isTemp; }
		inline std::string getValue() const { return value; }
		inline std::string getType() const { return type; }
		Term(std::string value, std::string type);
		~Term();
		virtual void createData(std::string & code) override;
		// Inherited via BaseNode
		virtual void toCode(std::string & code) override;

		// Inherited via BoolNode
		virtual std::vector<std::string> toBoolCode(std::string & code) override;

		// Inherited via BaseNode
		virtual bool isCallFunction(std::string name) override;
	};
}


