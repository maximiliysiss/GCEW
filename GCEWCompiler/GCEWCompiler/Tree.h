#pragma once
#include <list>
#include "Enums.h"
#include "Element.h"
#include "CustomTypes.h"
#include "Variable.h"
#include "IfTree.h"
#include "CycleTree.h"

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
		std::list<CustomTypes*> customTypes;
		Tree* parent{ nullptr };
		bool isBlockList();
		virtual void createInnerCode(std::string & code);
	public:
		inline std::list<Element*> getElements() const { return operations; }
		Tree() = delete;
		Tree(int index, std::string line, RegexResult reg);
		virtual ~Tree();
		void treeChildrenPrinter(std::ostream & out, int level = 0);
		void variableInfoPrinter(std::ostream & out, int level = 0);
		CycleTree * findCycleTreeUp();
		IfTree * findIfTreePrev();
		void optimize();
		std::string createCode();
		std::vector<Tree*> getChildren();
		inline Tree* getParent() const { return parent; }
		Tree * addChild(Tree * child);
		Tree * getRoot();
		Variable * findVariableByName(std::string name);
		void addOperation(Element * elem);

		// Inherited via Element
		virtual void toCode(std::string & code) override;
	};
}

#endif