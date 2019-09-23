#include "Parser.h"

namespace gcew::commons
{
	static const std::vector<std::vector<OperationParser>> operationsOrder{
		{OperationParser(Operations::Plus),
		OperationParser(Operations::Minus),
		OperationParser(Operations::And, OperationParser::Two),
		OperationParser(Operations::Or, OperationParser::Two)},
		{OperationParser(Operations::Multiply),
		OperationParser(Operations::Divide),
		OperationParser(Operations::Greater),
		OperationParser(Operations::Lower),
		OperationParser(Operations::Equal, OperationParser::Two)},
		{OperationParser(Operations::Mod)}
	};

	Node * getOperation(std::string oper, BaseNode * l, BaseNode * r) {
		switch ((Operations)oper[0]) {
		case Operations::Plus:
			return new OperatorPlus(oper, l, r);
		case Operations::Minus:
			return new OperatorMinus(oper, l, r);
		case Operations::And:
			return new OperatorAnd(oper, l, r);
		case Operations::Divide:
			return new OperatorDivide(oper, l, r);
		case Operations::Equal:
			return new OperatorEqual(oper, l, r);
		case Operations::Greater:
			return new OperatorGreater(oper, l, r);
		case Operations::Lower:
			return new OperatorLower(oper, l, r);
		case Operations::Multiply:
			return new OperatorMultiply(oper, l, r);
		case Operations::Or:
			return new OperatorOr(oper, l, r);
		case Operations::Mod:
			return new OperatorMod(oper, l, r);
		}
		return nullptr;
	}

	OperationParser gcew::commons::getOperation(char c, int type) {
		const std::vector<OperationParser>& oper = operationsOrder[type];

		for (auto elem : oper) {
			if (elem.symbol == c) {
				return elem;
			}
		}
		return OperationParser();
	}

	BaseNode * step(int type, std::string str, int & level) {
		for (int i = static_cast<int>(str.length()) - 1; i >= 0; i--) {
			char c = str[i];
			if (c == '(') {
				level--;
				continue;
			}
			if (c == ')') {
				level++;
				continue;
			}
			if (level > 0)
				continue;
			auto oper = getOperation(c, type);
			if (oper.symbol != 0 && i != 0) {
				std::string left = str.substr(0, i - oper.type);
				std::string right = str.substr(i + 1);
				return getOperation(oper.getOperation(), gcew::commons::Parser::parser(left), gcew::commons::Parser::parser(right));
			}
		}
		return nullptr;
	}

	BaseNode * Parser::preParser(std::string str)
	{
		try {
			str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
			if (str.length() == 0)
				return nullptr;
			return parser(str);
		}
		catch (std::exception ex) {
			return nullptr;
		}
	}

	BaseNode * gcew::commons::Parser::parser(std::string str)
	{
		int level = 0;
		BaseNode * result = nullptr;
		for (short i = 0; i < 2; ++i) {
			result = step(i, str, level);
			if (result)
				return result;
		}
		if (str[0] == '(') {
			for (size_t i = 0; i < str.size(); ++i) {
				if (str[i] == '(') {
					++level;
					continue;
				}
				if (str[i] == ')') {
					--level;
					if (level == 0) {
						std::string exp(str.substr(1, i - 1));
						return parser(exp);
					}
					continue;
				}
			}
		}
		else if (gcew::regulars::TreeRegularBuilder::isFunctionInExpression(str) == gcew::regulars::RegexResult::Call) {
			return new CallNode(str);
		}
		else if (str[0] == Operations::Not)
			return new OperatorNot(std::string(1, Operations::Not), parser(str.substr(1)));
		else
			return new Term(str, "");
		return result;
	}
}
