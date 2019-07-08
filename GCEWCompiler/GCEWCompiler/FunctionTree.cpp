#include "FunctionTree.h"


gcew::trees::structural::FunctionTree::FunctionTree(int index, std::string line, gcew::regulars::RegexResult reg)
	:Tree(index, line, reg)
{
	auto parts = gcew::commons::splitter(line, ' ');
	outputType = parts[0];
	name = splitter(parts[1], '(')[0];
	auto indexOpen = line.find('(');
	auto indexClose = line.find(')');
	parts = splitter(line.substr(indexOpen + 1, indexClose - indexOpen - 1), ',');
	std::for_each(parts.begin(), parts.end(), [](std::string str) {str = trim(str); });
	arguments = parts;
}
