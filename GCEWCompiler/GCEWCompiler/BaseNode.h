#pragma once

#include <string>

namespace gcew::trees::parser
{

	class BaseNode
	{
	protected:
		std::string name;
	public:
		virtual void postWork(void * tree) {}
		virtual void toCode(std::string& code) = 0;
		virtual bool isCallFunction(std::string name) = 0;
		inline std::string getName() const { return name; }
		BaseNode();
		virtual void createData(std::string & code) {}
		virtual bool isInActiveTree(std::string name) { return false; }
		virtual ~BaseNode();
	};
}


