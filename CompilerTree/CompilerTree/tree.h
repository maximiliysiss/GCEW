#pragma once
#include <map>
#include <list>
#include <string>
#include <Windows.h>
#include <iostream>
#include <iomanip> 
#include "operation.h"
#include "instruments.h"
#include "mathParser.h"
#include "TreeBuilderRegex.h"

#ifndef TREE_H

class operation;
class assigment;
/*вывести линиии*/
void outputLine(std::ostream& out, std::list<std::string> columnsValue, int = 15);
/*переменная*/
struct variable {
	/*конструкторы*/
	variable(std::string ID, std::string type) : ID(ID), type(type) {}
	variable(std::string data);
	~variable() { delete treeValue; }
	/*имя*/
	std::string name;
	/*идентификатор*/
	std::string ID;
	/*тип*/
	std::string type;
	/*значение*/
	std::string value;
	/*получить данные из приравнивани*/
	std::string getValueFromData(std::string data);
	/*дерево выражения*/
	Exp * treeValue;
	/*получить создания сегмента data*/
	std::string getData() {
		std::string res;
		treeValue->getData(res);
		return res + name + " real8 ?\n";
	}
	/*получить инициализацию*/
	std::string getInit() {
		if (treeValue == nullptr)
			return "";
		std::string code;
		treeValue->init(name, code);
		code += "fstp " + name + "\n";
		return code;
	}
};

/*дерево*/
class tree
{
	/*родитель*/
	tree * parent{ nullptr };
	/*дети*/
	std::vector<tree *> children;
	/*операции*/
	std::vector<operation*> operations;
	/*переменные*/
	std::map<std::string, variable *> variables;
	/*уровень*/
	int level{ -1 };
	/*имя*/
	std::string name;
	/*тип дерева*/
	RegexResult result;
	/*увеличить уровень*/
	void incrementLevel();
public:
	/*получить имя*/
	tree * getByName(std::string name);
	/*напечтать дерево*/
	void treeChildrenPrinter(int level = 0) {
		auto name = this->name.length() == 0 ? "root" : this->name;
		std::cout << level << ": " << name << std::endl;
		for (auto child : children) {
			child->treeChildrenPrinter(level + 1);
		}
	}
	/*оптимизация*/
	void optimize();
	/*в блок листе?*/
	bool isBlockList();
	/*очередь для вставки в код*/
	int order;
	/*поиск цикла выше для break/continue*/
	tree * findCycles();
	/*получить данные*/
	virtual void createData(std::string& data);
	/*получить инициализацию*/
	void createInit(std::string& data);
	/*получить код*/
	std::string createCode();
	/*перегрузка вывода*/
	friend std::ostream & operator<<(std::ostream& out, const tree * root);
	/*получить доступных переменных*/
	std::list<std::string> getListOfAvailableVars();
	/*вывести таблицу*/
	void outputVars(std::ostream & out);
	/*получить родителя*/
	tree * getParent();
	/*констурктор*/
	tree(int, int, std::string, RegexResult);
	tree(int, int = -1);
	/*добавить детей*/
	tree * addChildren(tree * tr);
	/*создать внутренний код*/
	virtual void createCodeInner(std::string& code);
	virtual ~tree();
	/*получить детей*/
	const std::vector<tree *> & getChildren();
	/*получить переменные*/
	const std::map<std::string, variable *> & getVariables();
	/*получить корень дерева*/
	tree * tryGetRoot();
	/*перегрузка оператора*/
	const variable * operator[](std::string name);
	/*добавить переменную*/
	void addVariable(variable * var);
	/*добавить операцию*/
	operation* addOperation(std::string operation, int, RegexResult);
	/*получить вызовы*/
	std::list<operation*> getOperationsCalling();
	tree * getLastTree();
};

/*циклические деревья*/
class cycleTree : public tree {
public:
	cycleTree(int i, int order, std::string line, RegexResult reg) :tree(i, order, line, reg) {}
	/*начало*/
	std::string end;
	/*конец*/
	std::string start;
};

/*for*/
class forTree : public cycleTree {
protected:
	/*условие*/
	Exp* condition;
	/*первый аргумент*/
	operation * first;
	/*третий аргумент*/
	operation * third;
public:
	forTree(int i, int order, std::string line);
	void createCodeInner(std::string& code);
	void createData(std::string & data);
};

/*while*/
class whileTree : public cycleTree {
	/*условие*/
	Exp * condition;
public:
	whileTree(int i, int order, std::string line);
	void createCodeInner(std::string& code);
	void createData(std::string & data);
};

class elseTree : public tree {
public:
	elseTree(int i, int order, std::string line);
	void createCodeInner(std::string& code);
	void createCodeInner(std::string& code, bool f);
};

class ifTree : public tree {
	elseTree * elseTreeInner{ nullptr };
	Exp * condition;
public:
	ifTree(int i, int order, std::string line);
	void createCodeInner(std::string& code);
	void createData(std::string & data);
	void setElse(elseTree * tr) { elseTreeInner = tr; }
};

#endif // !TREE_H

