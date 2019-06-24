#pragma once
#ifndef ONENODE_H
#define ONENODE_H

#include "BaseNode.h"

namespace gcew::parser
{
	class OneNode :
		public BaseNode
	{
	private:
		std::string operation;
		BaseNode * node;
	public:
		OneNode(BaseNode * node, std::string operation);
		~OneNode();
	};
}

#endif // !ONENODE_H


