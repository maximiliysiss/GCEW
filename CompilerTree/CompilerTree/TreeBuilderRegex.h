#pragma once
#include <string>
#include <regex>
#include <list>
#ifndef TREEBUILDERREGEX_H

#include "Enums.h"
#include "tree.h"

class tree;

/*регулярки*/
class TreeBuilderRegex
{
public:
	/*текущее дерево*/
	static tree ** currentTree;
	/*получить оценку линии*/
	static RegexResult regex(std::string input);
private:
	/*указатель на функцию*/
	typedef RegexResult(*RegexValidate)(std::string);
	/*регулярки*/
	static std::list<RegexValidate> regexes;

	/*резулярки*/
	static RegexResult isType(std::string input);
	static RegexResult isFunction(std::string input);
	static RegexResult isProcedure(std::string input);
	static RegexResult isIf(std::string input);
	static RegexResult isWhile(std::string input);
	static RegexResult isFor(std::string input);
	static RegexResult isOpenFigure(std::string input);
	static RegexResult isCloseFigure(std::string input);
	static RegexResult isAssigment(std::string input);
	static RegexResult isCall(std::string input);
	static RegexResult isPrint(std::string input);
	static RegexResult isBreak(std::string input);
	static RegexResult isContinue(std::string input);	
};

#endif // !TREEBUILDERREGEX_H

