#include "OneNode.h"
#include "CallOperation.h"

namespace gcew::trees::parser
{
	void OneNode::createData(std::string & code)
	{
		node->createData(code);
	}

	OneNode::OneNode(BaseNode * node, std::string operation)
		: node(node), operation(operation)
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

	void CallNode::createData(std::string & code)
	{
		call->createData(code);
	}

	void CallNode::postWork(void * tree)
	{
		call->postWork(tree);
	}

	CallNode::CallNode(std::string operation)
		:OneNode(nullptr, operation)
	{
		this->call = new gcew::trees::elements::operations::CallOperation(0, operation + ";");
	}

	void CallNode::toCode(std::string & code)
	{
		call->toCode(code);
	}

}
