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
	};

	class OperatorNot : public OneNode {
	public:
		OperatorNot(std::string operation, BaseNode * node);
		virtual void toCode(std::string & code) override;
	};

	class CallNode : public OneNode {
		gcew::trees::elements::Element * call;
	public:
		virtual void createData(std::string & code) override;
		virtual void postWork(void * tree) override;
		CallNode(std::string operation);
		virtual void toCode(std::string & code) override;
	};
}

