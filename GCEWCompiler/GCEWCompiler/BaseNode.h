#pragma once
#ifndef BASENODE_H
#define BASENODE_H

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
		virtual ~BaseNode();
	};
}

#endif // !BASENODE_H


