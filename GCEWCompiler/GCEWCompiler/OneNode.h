#pragma once
#ifndef ONENODE_H
#define ONENODE_H

#include "BaseNode.h"

namespace gcew::trees::parser
{
	class OneNode :
		public BaseNode
	{
	protected:
		std::string operation;
		BaseNode * node;
	public:
		virtual void toCode(std::string & code) = 0;
		OneNode(BaseNode * node, std::string operation);
		~OneNode();
	};

	class OperatorNot : public OneNode {
		virtual void toCode(std::string & code) override;
	};
}

#endif // !ONENODE_H


