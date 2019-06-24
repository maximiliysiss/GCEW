#include "Tree.h"

namespace gcew::trees::structural
{

	Tree::Tree(int index, std::string line, RegexResult reg)
		: Element(index, line, reg)
	{
	}


	Tree::~Tree()
	{
		if (parent)
			delete parent;
	}

	void Tree::treeChildrenPrinter(std::ostream & out, int level)
	{
		auto name = this->line.length() == 0 ? "root" : this->line;
		out << level << ": " << name << std::endl;
		for (auto child : children) {
			child->treeChildrenPrinter(out, level + 1);
		}
	}

	void Tree::variableInfoPrinter(std::ostream & out, int level)
	{
	}

	Tree * Tree::addChild(Tree * child)
	{
		this->children.push_back(child);
		return child;
	}

	Tree * Tree::getRoot()
	{
		if (parent)
			return parent->getRoot();
		return this;
	}

	void Tree::addOperation(Element * elem)
	{
		this->operations.push_back(elem);
	}

}
