#pragma once
#ifndef NODE_H
#define NODE_H

#include "BaseNode.h"

namespace gcew::trees::parser
{
	class Node :
		public BaseNode
	{
	protected:
		std::string operation;
		BaseNode * left;
		BaseNode * right;
	public:
		Node(std::string operation, BaseNode * left, BaseNode * right);
		~Node();
	};
}

#endif // !NODE_H


