#pragma once
#ifndef PARSER_H
#define PARSER_H

#include "BaseNode.h"

namespace gcew::commons
{

	using namespace gcew::trees::parser;

	struct Parser
	{
		static BaseNode * parser(std::string str);
	};
}

#endif // !PARSER_H


