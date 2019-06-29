#pragma once
#ifndef ELSETREE_H
#define ELSETREE_H

#include "Tree.h"

namespace gcew::trees::structural
{
	class ElseTree :
		public Tree
	{
	public:
		ElseTree(int index, std::string line);
		~ElseTree();
	};
}


#endif // !ELSETREE_H

