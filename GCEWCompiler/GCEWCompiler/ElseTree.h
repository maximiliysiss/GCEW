#pragma once
#include "Tree.h"

namespace gcew::trees::structural
{
	class ElseTree :
		public Tree
	{
	public:
		virtual void toCode(std::string & code) override;
		void toElseCode(std::string& code);
		ElseTree(int index, std::string line);
		~ElseTree();
	};
}

