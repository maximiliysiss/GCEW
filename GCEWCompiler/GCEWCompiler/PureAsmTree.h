#pragma once
#include "Tree.h"

namespace gcew::trees::structural
{
	class PureAsmTree :
		public Tree
	{
		std::list<std::string> datas;
	public:
		PureAsmTree(int index, std::string line);
		inline void addLine(std::string str) { datas.push_back(str); }
		virtual void toCode(std::string & code);
	};

}
