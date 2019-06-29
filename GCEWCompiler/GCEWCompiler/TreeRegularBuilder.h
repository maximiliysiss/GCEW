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
	private:
		typedef RegexResult(*RegexValidate)(std::string);
		static std::list<RegexValidate> regexes;

		static RegexResult isInclude(std::string input);

		static RegexResult isPureAsm(std::string input);

		static RegexResult isType(std::string input);

		static RegexResult isFunction(std::string input);
		static RegexResult isClass(std::string input);
		static RegexResult isStruct(std::string input);
		static RegexResult isProcedure(std::string input);

		static RegexResult isIf(std::string input);
		static RegexResult isElse(std::string input);
		static RegexResult isWhile(std::string input);
		static RegexResult isFor(std::string input);

		static RegexResult isOpenFigure(std::string input);
		static RegexResult isCloseFigure(std::string input);

		static RegexResult isAssigment(std::string input);
		static RegexResult isCall(std::string input);

		static RegexResult isBreak(std::string input);
		static RegexResult isContinue(std::string input);
	};
}

#endif // !TREEREGULARBUILDER_H


