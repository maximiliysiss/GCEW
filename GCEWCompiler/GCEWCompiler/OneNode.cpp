#include "OneNode.h"

namespace gcew::trees::parser
{

	OneNode::OneNode(BaseNode * node, std::string operation)
		:node(node), operation(operation)
	{
	}

	OneNode::~OneNode()
	{
		if (node)
			delete node;
	}

	OperatorNot::OperatorNot(std::string operation, BaseNode * node)
		:OneNode(node, operation)
	{
	}

	void OperatorNot::toCode(std::string & code)
	{
	}

	CallNode::CallNode(std::string operation, BaseNode * node)
		:OneNode(node, operation)
	{
	}

	void CallNode::toCode(std::string & code)
	{
	}

}
