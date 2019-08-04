#pragma once
#include <string>
#include "CompileConfiguration.h"
#include "Instruments.h"

namespace gcew::trees::parser {
	class BoolNode
	{
	protected:
		std::string boolOperationName;
	public:
		inline std::string getBoolOperationName() const { return boolOperationName; }
		BoolNode(std::string operationType);
		virtual std::vector<std::string> toBoolCode(std::string& code) = 0;
		inline std::vector<std::string> getReturn() {
			return {
				gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::Start] + boolOperationName + ":",
				gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolTrue] + boolOperationName + ":",
				gcew::commons::CompileConfiguration::typeOperation["bool"][gcew::commons::Operations::BoolFalse] + boolOperationName + ":"
			};
		}
		virtual ~BoolNode();
	};
}

