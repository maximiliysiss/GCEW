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

	OperatorGreater::OperatorGreater(std::string operation, BaseNode * left, BaseNode * right)
		:Node(operation, left, right)
	{
	}

	void OperatorGreater::toCode(std::string & code)
	{
	}

	void OperatorLower::toCode(std::string & code)
	{
	}

	void OperatorEqual::toCode(std::string & code)
	{
	}

}
