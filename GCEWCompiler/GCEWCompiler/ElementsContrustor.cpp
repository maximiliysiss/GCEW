#include "ElementsContrustor.h"

gcew::trees::elements::Element * gcew::trees::construct_elements(gcew::regulars::RegexResult reg, int index, std::string line)
{
	switch (reg) {
	case RegexResult::Type:
		return new Variable(index, line);
	case RegexResult::Assigment:
		return new gcew::trees::elements::operations::AssigmentOperation(index, line);
	case RegexResult::Break:
		return new BreakOperation(index, line);
	case RegexResult::Call:
		return new CallOperation(index, line);
	case RegexResult::Continue:
		return new ContinueOperation(index, line);
	case RegexResult::Else:
		return new ElseTree(index, line);
	case RegexResult::For:
		return new ForTree(index, line);
	case RegexResult::Function:
	case RegexResult::Procedure:
		return new FunctionTree(index, line, reg);
	case RegexResult::If:
		return new IfTree(index, line);
	case RegexResult::PureAsm:
		return new PureAsmTree(index, line);
	case RegexResult::Return:
		return new ReturnOperation(index, line);
	case RegexResult::While:
		return new WhileTree(index, line);
	}
	return nullptr;
}