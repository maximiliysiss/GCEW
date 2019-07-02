#include "TreeRegularBuilder.h"

namespace gcew::regulars
{

	std::list<TreeRegularBuilder::RegexValidate> TreeRegularBuilder::regexes = {
		TreeRegularBuilder::isAssigment,
		TreeRegularBuilder::isBreak,
		TreeRegularBuilder::isCall,
		TreeRegularBuilder::isCloseFigure,
		TreeRegularBuilder::isContinue,
		TreeRegularBuilder::isElse,
		TreeRegularBuilder::isFor,
		TreeRegularBuilder::isProcedure,
		TreeRegularBuilder::isFunction,
		TreeRegularBuilder::isIf,
		TreeRegularBuilder::isInclude,
		TreeRegularBuilder::isOpenFigure,
		TreeRegularBuilder::isPureAsm,
		TreeRegularBuilder::isType,
		TreeRegularBuilder::isWhile,
		TreeRegularBuilder::isReturn
	};

	RegexResult TreeRegularBuilder::regex(std::string input)
	{
		for (auto reg : regexes) {
			auto regResult = reg(input);
			if (regResult != RegexResult::NotClassic)
				return regResult;
		}
		return RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isInclude(std::string input)
	{
		std::regex reg("^#include [a-zA-Z]+([a-zA-Z0-9])*(.gcew)*$");
		if (std::regex_match(input, reg))
			return RegexResult::Include;
		return RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isPureAsm(std::string input)
	{
		std::regex reg("^pureasm$");
		if (std::regex_match(input, reg))
			return RegexResult::PureAsm;
		return RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isType(std::string input)
	{
		std::regex reg("^[a-zA-Z]+[a-z-A-Z0-9]* [a-zA-Z]+[a-zA-Z0-9]*( = .*)*;$");
		if (std::regex_match(input, reg))
			return RegexResult::Type;
		return RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isFunction(std::string input)
	{
		std::regex reg("^[a-zA-Z]+[a-zA-Z0-9]* [a-zA-Z]+[a-zA-Z0-9]*\\(.*\\)$");
		if (std::regex_match(input, reg))
			return RegexResult::Function;
		return RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isProcedure(std::string input)
	{
		std::regex reg("^void [a-zA-Z]+[a-zA-Z0-9]*\\(.*\\)$");
		if (std::regex_match(input, reg))
			return RegexResult::Procedure;
		return RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isIf(std::string input)
	{
		std::regex reg("^if\\(.+\\)$");
		if (std::regex_match(input, reg))
			return RegexResult::If;
		return RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isElse(std::string input)
	{
		std::regex reg("^else$");
		if (std::regex_match(input, reg))
			return RegexResult::Else;
		return RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isWhile(std::string input)
	{
		std::regex reg("^while\\(.+\\)$");
		if (std::regex_match(input, reg))
			return RegexResult::While;
		return RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isFor(std::string input)
	{
		std::regex reg("^for\\(.*;.*;.*\\)$");
		if (std::regex_match(input, reg))
			return RegexResult::For;
		return RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isOpenFigure(std::string input)
	{
		std::regex reg("^\\{$");
		if (std::regex_match(input, reg))
			return RegexResult::FigureOpen;
		return RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isCloseFigure(std::string input)
	{
		std::regex reg("^\\}$");
		if (std::regex_match(input, reg))
			return RegexResult::FigureClose;
		return RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isAssigment(std::string input)
	{
		std::regex reg("^[a-zA-Z]+[a-zA-Z0-9]* = .*;$");
		if (std::regex_match(input, reg))
			return RegexResult::Assigment;
		return RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isCall(std::string input)
	{
		std::regex reg("^[a-zA-Z]+[a-zA-Z0-9]*\\(.*\\);$");
		if (std::regex_match(input, reg))
			return RegexResult::Call;
		return RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isBreak(std::string input)
	{
		std::regex reg("^break;$");
		if (std::regex_match(input, reg))
			return RegexResult::Break;
		return RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isContinue(std::string input)
	{
		std::regex reg("^continue;$");
		if (std::regex_match(input, reg))
			return RegexResult::Continue;
		return RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isReturn(std::string input)
	{
		std::regex reg("^return .*;$");
		if (std::regex_match(input, reg))
			return RegexResult::Return;
		return RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isFunctionInExpression(std::string input)
	{
		std::regex reg("^[a-zA-Z]+[a-zA-Z0-9]*[^*+-\\/]*\\(.+\\)$");
		if (std::regex_match(input, reg))
			return RegexResult::Call;
		return RegexResult::NotClassic;
	}
}
