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

	OperatorLower::OperatorLower(std::string operation, BaseNode * left, BaseNode * right)
		:Node(operation, left, right)
	{
	}

	void OperatorLower::toCode(std::string & code)
	{
	}

	OperatorEqual::OperatorEqual(std::string operation, BaseNode * left, BaseNode * right)
		:Node(operation, left, right)
	{
	}

	void OperatorEqual::toCode(std::string & code)
	{
	}

	OperatorNotEqual::OperatorNotEqual(std::string operation, BaseNode * left, BaseNode * right)
		:Node(operation, left, right)
	{
	}

	void OperatorNotEqual::toCode(std::string & code)
	{
	}

	OperatorAnd::OperatorAnd(std::string operation, BaseNode * left, BaseNode * right)
		:Node(operation, left, right)
	{
	}

	void OperatorAnd::toCode(std::string & code)
	{
	}

	OperatorOr::OperatorOr(std::string operation, BaseNode * left, BaseNode * right)
		:Node(operation, left, right)
	{
	}

	void OperatorOr::toCode(std::string & code)
	{
	}

	OperatorPlus::OperatorPlus(std::string operation, BaseNode * left, BaseNode * right)
		:Node(operation, left, right)
	{
	}

	void OperatorPlus::toCode(std::string & code)
	{
		left->toCode(code);
		right->toCode(code);
		code += gcew::commons::CompileConfiguration::typeOperation[COMMONS][Operations::Plus] + "\n";
	}

	OperatorMinus::OperatorMinus(std::string operation, BaseNode * left, BaseNode * right)
		:Node(operation, left, right)
	{
	}

	void OperatorMinus::toCode(std::string & code)
	{
		left->toCode(code);
		right->toCode(code);
		code += gcew::commons::CompileConfiguration::typeOperation[COMMONS][Operations::Minus] + "\n";
	}

	OperatorMultiply::OperatorMultiply(std::string operation, BaseNode * left, BaseNode * right)
		:Node(operation, left, right)
	{
	}

	void OperatorMultiply::toCode(std::string & code)
	{
		left->toCode(code);
		right->toCode(code);
		code += gcew::commons::CompileConfiguration::typeOperation[COMMONS][Operations::Multiply] + "\n";
	}

	OperatorDivide::OperatorDivide(std::string operation, BaseNode * left, BaseNode * right)
		:Node(operation, left, right)
	{
	}

	void OperatorDivide::toCode(std::string & code)
	{
		left->toCode(code);
		right->toCode(code);
		code += gcew::commons::CompileConfiguration::typeOperation[COMMONS][Operations::Divide] + "\n";
	}

	OperatorMod::OperatorMod(std::string operation, BaseNode * left, BaseNode * right)
		:Node(operation, left, right)
	{
	}

	void OperatorMod::toCode(std::string & code)
	{
	}

}
