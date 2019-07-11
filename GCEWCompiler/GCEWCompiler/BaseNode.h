#pragma once
#ifndef BASENODE_H
#define BASENODE_H

#include <string>
#include "Instruments.h"
#include "CompileConfiguration.h"

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

#endif // !BASENODE_H


