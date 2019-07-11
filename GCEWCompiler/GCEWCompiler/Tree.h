#pragma once
#include <vector>
#include <list>
#include "Enums.h"
#include "Element.h"
#include "Instruments.h"
#include "CustomTypes.h"
#include "Variable.h"

namespace gcew::trees::structural
{
	using namespace gcew::trees::elements;

	class CycleTree;
	class IfTree;

	class Tree :
		public Element
	{
	protected:
		std::list<Element*> operations;
		std::list<CustomTypes*> customTypes;
		Tree* parent{ nullptr };
		bool isBlockList();
		virtual void createInnerCode(std::string & code);
		virtual void createInitializeData(std::string & code);
		virtual void createData(std::string & code);
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
		std::vector<Variable*> getVariables();
		void addOperation(Element * elem);

		// Inherited via Element
		virtual void toCode(std::string & code) override;
	};
}