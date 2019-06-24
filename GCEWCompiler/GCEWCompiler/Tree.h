#pragma once
#include <list>
#include "Enums.h"
#include "Element.h"
#include "CustomTypes.h"

#ifndef TREE_H
#define TREE_H

namespace gcew::trees::structural
{
	using namespace gcew::trees::elements;

	class Tree :
		public Element
	{
	protected:
		std::list<Element*> operations;
		std::list<Tree*> children;
		std::list<CustomTypes*> customTypes;
		Tree* parent{ nullptr };
		bool isBlockList();
		virtual void createInnerCode(std::string & code);
	public:
		inline std::list<Element*> getElements() const { return operations; }
		inline std::list<Tree*> getChildren() const { return children; }
		Tree() = delete;
		Tree(int index, std::string line, RegexResult reg);
		virtual ~Tree();
		void treeChildrenPrinter(std::ostream & out, int level = 0);
		void variableInfoPrinter(std::ostream & out, int level = 0);
		void optimize();
		std::string createCode();
		inline Tree* getParent() const { return parent; }
		Tree * addChild(Tree * child);
		Tree * getRoot();
		void addOperation(Element * elem);
	};
}

#endif