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
		std::string outputType;
		std::vector<gcew::trees::elements::Variable*> arguments;
		bool isMainFunction;
		void generateCodeForMain(std::string & code);
	protected:
		virtual void createInitializeData(std::string & code);
	public:
		inline bool isMain() const { return isMainFunction; }
		virtual void toCode(std::string& code) override;
		FunctionTree(int index, std::string line, gcew::regulars::RegexResult reg);
	};
}

