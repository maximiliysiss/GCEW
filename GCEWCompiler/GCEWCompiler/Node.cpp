#include "Node.h"

namespace gcew::trees::parser
{

	Node::Node(std::string operation, BaseNode * left, BaseNode * right)
		:operation(operation), left(left), right(right)
	{
	}

	Node::~Node()
	{
		if (left)
			delete left;
		if (right)
			delete right;
	}

}
