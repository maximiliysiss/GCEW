#include "PureAsmTree.h"

gcew::trees::structural::PureAsmTree::PureAsmTree(int index, std::string line)
	:Tree(index, line, gcew::regulars::RegexResult::PureAsm)
{
}

void gcew::trees::structural::PureAsmTree::toCode(std::string & code)
{
	for (auto str : datas)
		code += str + "\n";
}
