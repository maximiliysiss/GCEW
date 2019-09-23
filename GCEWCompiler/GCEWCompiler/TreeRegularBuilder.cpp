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
		TreeRegularBuilder::isReturn,
		TreeRegularBuilder::isType,
		TreeRegularBuilder::isWhile,
	};

	RegexResult TreeRegularBuilder::regex(std::string input)
	{
		for (auto reg : regexes) {
			auto regResult = reg(input, true);
			if (regResult != RegexResult::NotClassic)
				return regResult;
		}
		return RegexResult::NotClassic;
	}

	std::list<RegexResult> TreeRegularBuilder::regexMatching(std::string input)
	{
		std::list<RegexResult> result;
		for (auto reg : regexes) {
			auto regResult = reg(input, false);
			if (regResult != RegexResult::NotClassic)
				result.push_back(regResult);
		}
		return result;
	}

	bool TreeRegularBuilder::regex_matcher(std::string reg, std::string input, bool type)
	{
		if (input.length() == 0)
			return false;
		std::regex regular(type ? reg : reg.substr(1, reg.length() - 2));
		return std::regex_search(input, regular);
	}

	RegexResult TreeRegularBuilder::isInclude(std::string input, bool type)
	{
		return regex_matcher("^using [a-zA-Z]+([a-zA-Z0-9])*(.gcew)*;$", input, type) ? RegexResult::Include : RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isPureAsm(std::string input, bool type)
	{
		return regex_matcher("^pureasm$", input, type) ? RegexResult::PureAsm : RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isType(std::string input, bool type)
	{
		return regex_matcher("^[a-zA-Z]+[a-z-A-Z0-9]* [a-zA-Z]+[a-zA-Z0-9]*( = .*)*;$", input, type) ? RegexResult::Type : RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isFunction(std::string input, bool type)
	{
		return regex_matcher("^[a-zA-Z]+[a-zA-Z0-9]* [a-zA-Z]+[a-zA-Z0-9]*\\(.*\\)$", input, type) ? RegexResult::Function : RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isProcedure(std::string input, bool type)
	{
		return regex_matcher("^void [a-zA-Z]+[a-zA-Z0-9]*\\(.*\\)$", input, type) ? RegexResult::Procedure : RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isIf(std::string input, bool type)
	{
		return regex_matcher("^if\\(.+\\)$", input, type) ? RegexResult::If : RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isElse(std::string input, bool type)
	{
		return regex_matcher("^else$", input, type) ? RegexResult::Else : RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isWhile(std::string input, bool type)
	{
		return regex_matcher("^while\\(.+\\)$", input, type) ? RegexResult::While : RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isFor(std::string input, bool type)
	{
		return regex_matcher(getForRegex(), input, type) ? RegexResult::For : RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isOpenFigure(std::string input, bool type)
	{
		return regex_matcher("^\\{$", input, type) ? RegexResult::FigureOpen : RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isCloseFigure(std::string input, bool type)
	{
		return regex_matcher("^\\}$", input, type) ? RegexResult::FigureClose : RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isAssigment(std::string input, bool type)
	{
		return regex_matcher("^[a-zA-Z]+[a-zA-Z0-9]* = .*;$", input, type) ? RegexResult::Assigment : RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isCall(std::string input, bool type)
	{
		return regex_matcher("^[a-zA-Z]+[a-zA-Z0-9]*\\(.*\\);$", input, type) ? RegexResult::Call : RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isBreak(std::string input, bool type)
	{
		return regex_matcher("^break;$", input, type) ? RegexResult::Break : RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isContinue(std::string input, bool type)
	{
		return regex_matcher("^continue;$", input, type) ? RegexResult::Continue : RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isReturn(std::string input, bool type)
	{
		return regex_matcher("^return *.*;$", input, type) ? RegexResult::Return : RegexResult::NotClassic;
	}

	RegexResult TreeRegularBuilder::isFunctionInExpression(std::string input)
	{
		std::regex reg("^[a-zA-Z]+[a-zA-Z0-9]*[^*+-\\/]*\\(.*\\)$");
		if (std::regex_match(input, reg))
			return RegexResult::Call;
		return RegexResult::NotClassic;
	}

	std::string TreeRegularBuilder::isVariableInPureAsm(std::string input)
	{
		std::regex reg("var\\(.*\\)");
		std::smatch sm;
		if (std::regex_search(input, sm, reg)) {
			return sm[0];
		}
		return "";
	}

	std::string TreeRegularBuilder::getForRegex()
	{
		return "^for\\(.*;.*;.*\\)$";
	}
}
