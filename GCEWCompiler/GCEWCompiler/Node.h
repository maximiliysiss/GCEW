#pragma once
#ifndef NODE_H
#define NODE_H

#include "BaseNode.h"
#include "Element.h"

namespace gcew::trees::parser
{
	using namespace gcew::trees::elements;

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

	class OperatorGreater : public Node {
	public:
		OperatorGreater(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(std::string & code) override;
	};

	class OperatorLower : public Node {
	public:
		OperatorLower(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(std::string & code) override;
	};

	class OperatorEqual : public Node {
	public:
		OperatorEqual(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(std::string & code) override;
	};

	class OperatorNotEqual : public Node {
	public:
		OperatorNotEqual(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(std::string & code) override;
	};

	class OperatorAnd : public Node {
	public:
		OperatorAnd(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(std::string & code) override;
	};

	class OperatorOr : public Node {
	public:
		OperatorOr(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(std::string & code) override;
	};

	class OperatorPlus : public Node {
	public:
		OperatorPlus(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(std::string & code) override;
	};

	class OperatorMinus : public Node {
	public:
		OperatorMinus(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(std::string & code) override;
	};

	class OperatorMultiply : public Node {
	public:
		OperatorMultiply(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(std::string & code) override;
	};

	class OperatorDivide : public Node {
	public:
		OperatorDivide(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(std::string & code) override;
	};

	class OperatorMod : public Node {
	public:
		OperatorMod(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(std::string & code) override;
	};
}

#endif // !NODE_H


