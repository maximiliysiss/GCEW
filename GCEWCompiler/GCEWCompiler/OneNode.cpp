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

	bool OneNode::isCallFunction(std::string name)
	{
		return this->node->isCallFunction(name);
	}

	OperatorNot::OperatorNot(std::string operation, BaseNode * node)
		:OneNode(node, operation)
	{
	}

	void OperatorNot::toCode(std::string & code)
	{
	}

	bool CallNode::isCallFunction(std::string name)
	{
		return call->isCallFunction(name);
	}

	void CallNode::createData(std::string & code)
	{
		call->createData(code);
	}

	void CallNode::postWork(void * tree)
	{
		call->postWork(tree);
	}

	bool CallNode::isInActiveTree(std::string name)
	{
		return ((gcew::trees::elements::operations::CallOperation*)this->call)->getFunctionName() == name;
	}

	CallNode::CallNode(std::string operation)
		:OneNode(nullptr, operation)
	{
		this->call = new gcew::trees::elements::operations::CallOperation(0, operation + ";");
		dynamic_cast<gcew::trees::elements::operations::CallOperation*>(this->call)
			->setTree(*gcew::trees::structural::Tree::currentTree);
	}

	void CallNode::toCode(std::string & code)
	{
		call->toCode(code);
	}

}
