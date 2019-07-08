#include "PureAsmTree.h"

gcew::trees::structural::PureAsmTree::PureAsmTree(int index, std::string line)
	:Tree(index, line, gcew::regulars::RegexResult::PureAsm)
{
}
