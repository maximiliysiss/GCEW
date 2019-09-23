#pragma once
#ifndef TREEREGULARBUILDER_H
#define TREEREGULARBUILDER_H

#include "Enums.h"
#include <string>
#include <list>
#include <regex>

namespace gcew::regulars
{
	using namespace gcew::commons;

	class TreeRegularBuilder
	{
	public:
		static RegexResult regex(std::string input);
		static std::list<RegexResult> regexMatching(std::string input);
	private:
		typedef RegexResult(*RegexValidate)(std::string, bool);

		static bool regex_matcher(std::string reg, std::string input, bool type);

		static std::list<RegexValidate> regexes;

		static RegexResult isInclude(std::string input, bool);

		static RegexResult isPureAsm(std::string input, bool);

		static RegexResult isType(std::string input, bool);

		static RegexResult isFunction(std::string input, bool);
		static RegexResult isClass(std::string input, bool);
		static RegexResult isStruct(std::string input, bool);
		static RegexResult isProcedure(std::string input, bool);

		static RegexResult isIf(std::string input, bool);
		static RegexResult isElse(std::string input, bool);
		static RegexResult isWhile(std::string input, bool);
		static RegexResult isFor(std::string input, bool);

		static RegexResult isOpenFigure(std::string input, bool);
		static RegexResult isCloseFigure(std::string input, bool);

		static RegexResult isAssigment(std::string input, bool);
		static RegexResult isCall(std::string input, bool);

		static RegexResult isBreak(std::string input, bool);
		static RegexResult isContinue(std::string input, bool);
		static RegexResult isReturn(std::string input, bool);
	public:
		static RegexResult isFunctionInExpression(std::string input);
		static std::string isVariableInPureAsm(std::string input);

		static std::string getForRegex();
	};
}

#endif // !TREEREGULARBUILDER_H


