#pragma once
#include "Tree.h"

namespace gcew::trees::structural
{
	class PureAsmTree :
		public Tree
	{
		std::list<std::string> datas;
		virtual bool isBlockForOptimize() override;
	public:
		PureAsmTree(int index, std::string line);
		void addLine(std::string str);
		virtual void toCode(std::string & code);
		virtual void postWork(void * tree) override;
	};

}
