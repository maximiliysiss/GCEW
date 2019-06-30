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
		OperatorGreater(std::string operation, BaseNode * left, BaseNode * right);
		virtual void toCode(std::string & code) override;
	};

	class OperatorLower : public Node {
		virtual void toCode(std::string & code) override;
	};

	class OperatorEqual : public Node {
		virtual void toCode(std::string & code) override;
	};

	class OperatorNotEqual : public Node {
		virtual void toCode(std::string & code) override;
	};

	class OperatorAnd : public Node {
		virtual void toCode(std::string & code) override;
	};

	class OperatorOr : public Node {
		virtual void toCode(std::string & code) override;
	};

	class OperatorPlus : public Node {
		virtual void toCode(std::string & code) override;
	};

	class OperatorMinus : public Node {
		virtual void toCode(std::string & code) override;
	};

	class OperatorMultiply : public Node {
		virtual void toCode(std::string & code) override;
	};

	class OperatorDivide : public Node {
		virtual void toCode(std::string & code) override;
	};

	class OperatorMod : public Node {
		virtual void toCode(std::string & code) override;
	};
}

#endif // !NODE_H


