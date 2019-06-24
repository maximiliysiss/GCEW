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

}
