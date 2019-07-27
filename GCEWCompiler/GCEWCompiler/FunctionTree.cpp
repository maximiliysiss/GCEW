#include "FunctionTree.h"


void gcew::trees::structural::FunctionTree::generateCodeForMain(std::string & code)
{
	code += "start:\n";
	Tree::toCode(code);
	code += "exit\nend start\n";
}

void gcew::trees::structural::FunctionTree::createInitializeData(std::string & code)
{
	for (auto arg : arguments)
		code += gcew::commons::CompileConfiguration::typeOperation[arg->getType()][gcew::commons::Operations::FieldSet]
		+ " " + arg->getName() + "\n";
}

void gcew::trees::structural::FunctionTree::toCode(std::string & code)
{
	if (isMainFunction) {
		generateCodeForMain(code);
		return;
	}
	code += name + "proc near\n";

}

void gcew::trees::structural::FunctionTree::createData(std::string & code)
{
	for (auto arg : arguments)
		arg->createInitializeData(code);
}

gcew::trees::structural::FunctionTree::FunctionTree(int index, std::string line, gcew::regulars::RegexResult reg)
	:Tree(index, line, reg)
{
	auto parts = gcew::commons::splitter(line, ' ');
	outputType = parts[0];
	name = gcew::commons::splitter(parts[1], '(')[0];
	auto indexOpen = line.find('(');
	auto indexClose = line.find(')');
	parts = gcew::commons::splitter(line.substr(indexOpen + 1, indexClose - indexOpen - 1), ',');
	std::for_each(parts.begin(), parts.end(), [](std::string str) {str = gcew::commons::trim(str); });
	std::transform(parts.begin(), parts.end(), std::back_inserter(arguments), [](std::string arg) {
		return new gcew::trees::elements::Variable(0, arg);
	});
	isMainFunction = this->name == "main";
}

