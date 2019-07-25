#pragma once

#include <string>

namespace gcew::trees::parser
{

	class BaseNode
	{
	protected:
		std::string name;
	public:
		virtual void toCode(std::string& code) = 0;
		BaseNode();
		virtual void createData(std::string & code) {}
		virtual ~BaseNode();
	};
}


