#include "PureAsmTree.h"

bool gcew::trees::structural::PureAsmTree::isBlockForOptimize()
{
	return this->datas.empty();
}

gcew::trees::structural::PureAsmTree::PureAsmTree(int index, std::string line)
	:Tree(index, line, gcew::regulars::RegexResult::PureAsm)
{
}

void gcew::trees::structural::PureAsmTree::addLine(std::string str)
{
	this->datas.push_back(str);
}

void gcew::trees::structural::PureAsmTree::toCode(std::string & code)
{
	for (auto str : datas)
		code += str + "\n";
}

void gcew::trees::structural::PureAsmTree::postWork(void * tree)
{
	auto t = (Tree*)tree;
	for (std::string& str : datas) {
		std::string tmp;
		while ((tmp = gcew::regulars::TreeRegularBuilder::isVariableInPureAsm(str)).length() > 0) {
			auto indexStart = tmp.find("(");
			auto indexEnd = tmp.find(")");
			tmp = tmp.substr(indexStart + 1, indexEnd - indexStart - 1);
			auto var = t->findVariableByName(tmp);
			tmp = "var(" + tmp + ")";
			auto indexTmp = str.find(tmp);
			str.replace(indexTmp, tmp.length(), var->getCodeName());
		}
	}
}
