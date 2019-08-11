#pragma once
#include "CompileConfiguration.h"
#include "Tree.h"

namespace  gcew::trees::elements
{
	class Variable;
}

namespace gcew::trees::structural
{

	class FunctionTree :
		public Tree
	{
		std::string functionName;
		std::string outputType;
		std::vector<gcew::trees::elements::Variable*> arguments;
		bool isMainFunction;
		void generateCodeForMain(std::string & code);
		virtual void createData(std::string & code);
	protected:
		virtual void createInitializeData(std::string & code);
		virtual gcew::trees::elements::Variable * findVariableByName(std::string name) override;
		virtual bool isBlockForOptimize() override;
	public:
		inline std::string getFuncName() const { return functionName; }
		inline bool isMain() const { return isMainFunction; }
		virtual void toCode(std::string& code) override;
		FunctionTree(int index, std::string line, gcew::regulars::RegexResult reg);
	};
}

