#include "Tree.h"

namespace gcew::trees::structural
{
	bool Tree::isBlockList()
	{
		return false;
	}
	void Tree::createInnerCode(std::string & code)
	{
	}
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
		for (Tree* child : this->getChildren()) {
			child->treeChildrenPrinter(out, level + 1);
		}
	}

	void Tree::variableInfoPrinter(std::ostream & out, int level)
	{
	}

	CycleTree * Tree::findCycleTreeUp()
	{
		if (this->nodeType == RegexResult::For || this->nodeType == RegexResult::While)
			return (CycleTree*)this;
		if (!this->parent)
			return nullptr;
		return this->parent->findCycleTreeUp();
	}

	IfTree * Tree::findIfTreePrev()
	{
		if (typeid(*(this->getChildren().end() - 1)) == typeid(IfTree*))
			return (IfTree*)*(this->getChildren().end() - 1);
		return nullptr;
	}

	void Tree::optimize()
	{
	}

	std::string Tree::createCode()
	{
		return std::string();
	}

	std::vector<Tree*> Tree::getChildren()
	{
		std::vector<Tree*> children;
		for (elements::Element* tr : this->operations)
			if (typeid(*tr) == typeid(Tree))
				children.push_back((Tree*)tr);
		return children;
	}

	Tree * Tree::addChild(Tree * child)
	{
		child->parent = this;
		this->operations.push_back(child);
		return child;
	}

	Tree * Tree::getRoot()
	{
		if (parent)
			return parent->getRoot();
		return this;
	}

	Variable * Tree::findVariableByName(std::string name)
	{
		for (auto elem : this->operations)
			if (typeid(*elem) == typeid(Variable)
				&& ((Variable*)elem)->getName() == name)
				return (Variable*)elem;
		return nullptr;
	}

	void Tree::addOperation(Element * elem)
	{
		this->operations.push_back(elem);
	}

	void Tree::toCode(std::string & code)
	{
	}

}
