#pragma once
#ifndef PARSER_H
#define PARSER_H

#include "BaseNode.h"
#include "Instruments.h"
#include "Node.h"
#include "Term.h"
#include "TreeRegularBuilder.h"
#include "OneNode.h"
#include <algorithm>

namespace gcew::commons
{
	enum Operations {
		FieldSet = 0,
		Convert = 1,
		Plus = '+',
		Minus = '-',
		Multiply = '*',
		Divide = '/',
		And = '&',
		Or = '|',
		Greater = '>',
		Lower = '<',
		Equal = '=',
		Not = '!',
		Mod = '%'
	};

	using namespace gcew::trees::parser;

	struct OperationParser {
		enum TypeParser {
			One, Two
		};

		inline std::string getOperation() const {
			if (type == TypeParser::Two)
				return std::string(2, symbol);
			return std::string(1, symbol);
		}

		OperationParser() : symbol(0) {}
		OperationParser(const OperationParser& o) {
			this->symbol = o.symbol;
			this->type = o.type;
		}

		OperationParser(char symbol, TypeParser type = TypeParser::One)
			:symbol(symbol), type(type) {}

		char symbol;
		TypeParser type;
	};

	struct Parser
	{
		static BaseNode * preParser(std::string str);
		static BaseNode * parser(std::string str);
	};

	OperationParser getOperation(char c, int type);
}

#endif // !PARSER_H


