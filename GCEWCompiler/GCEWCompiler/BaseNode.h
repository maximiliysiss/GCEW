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
		BaseNode();
		virtual ~BaseNode();
	};
}

#endif // !BASENODE_H


