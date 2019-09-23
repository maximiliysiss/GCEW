#pragma once
#include "Tree.h"
#include "BaseNode.h"

namespace gcew::trees::structural
{
	using namespace gcew::trees::parser;

	class CycleTree :
		public Tree
	{
	protected:
		BaseNode * condition{ nullptr };
		virtual void createData(std::string & code);
		std::string breakOperation;
		std::string continueOperation;
	public:
		virtual bool isCallFunction(std::string name) override;
		virtual void postWork(void * tree) override;
		virtual bool isInActiveTree(std::string name);
		inline std::string getContinue()const { return continueOperation; }
		inline std::string getBreak()const { return breakOperation; }
		CycleTree(int index, std::string line, gcew::commons::RegexResult reg);
		~CycleTree();
	};
}


