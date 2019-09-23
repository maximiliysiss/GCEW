#pragma once

#include "BaseNode.h"

namespace gcew::trees::elements
{
	class Element;
}

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
		virtual void createData(std::string & code);
		OneNode(BaseNode * node, std::string operation);
		~OneNode();

		// Inherited via BaseNode
		virtual bool isCallFunction(std::string name) override;
	};

	class OperatorNot : public OneNode {
	public:
		OperatorNot(std::string operation, BaseNode * node);
		virtual void toCode(std::string & code) override;
	};

	class CallNode : public OneNode {
		gcew::trees::elements::Element * call;
	public:
		virtual bool isCallFunction(std::string name) override;
		virtual void createData(std::string & code) override;
		virtual void postWork(void * tree) override;
		virtual bool isInActiveTree(std::string name) override;
		CallNode(std::string operation);
		virtual void toCode(std::string & code) override;
	};
}

