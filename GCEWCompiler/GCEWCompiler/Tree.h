#pragma once
#include <vector>
#include <list>
#include "Element.h"
#include "Instruments.h"
#include "CustomTypes.h"
#include "Variable.h"

namespace gcew::trees::structural
{
	class CycleTree;
	class IfTree;
	class FunctionTree;
}

namespace  gcew::trees::elements
{
	class Variable;
}


namespace gcew::trees::structural
{
	class Tree :
		public gcew::trees::elements::Element
	{
	protected:
		std::list<gcew::trees::elements::Element*> operations;
		std::list<gcew::trees::elements::CustomTypes*> customTypes;
		Tree* parent{ nullptr };
		bool isBlockList();
		virtual void createInitializeData(std::string & code);
		virtual void createData(std::string & code);
	public:
		static Tree ** currentTree;
		inline std::list<Element*> getElements() const { return operations; }
		Tree() = delete;
		Tree(int index, std::string line, gcew::commons::RegexResult reg);
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
		gcew::trees::elements::Variable * findVariableByName(std::string name);
		std::vector<gcew::trees::elements::Variable*> getVariables();
		void addOperation(Element * elem);
		std::vector<Element*> getElementsForInit();
		// Inherited via Element
		virtual void toCode(std::string & code) override;
	};
}