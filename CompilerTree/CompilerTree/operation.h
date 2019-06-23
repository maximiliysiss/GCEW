#pragma once
#include <string>
#include "Enums.h"
#include "mathParser.h"
#include "tree.h"
#include "instruments.h"

class TreeBuilderRegex;
class cycleTree;
class tree;

/*операции*/
class operation
{
protected:
	/*сырые данные*/
	std::string lineOnOperation;
	/*имя*/
	std::string name;
public:
	/*очередь*/
	int order;
	/*расчитать*/
	virtual void calculate() = 0;
	/*превратить к код*/
	virtual std::string toCode(std::string & code) = 0;
	/*получить переменные*/
	virtual void getData(std::string & code);
	/*получить операцию*/
	static operation * getOperation(RegexResult, int, std::string, tree* = nullptr);
	/*конструкторы*/
	operation(std::string line) :lineOnOperation(line) {}
	operation();
	virtual ~operation();
	/*получить имя*/
	std::string getName() { return name; }
	/*дерево выражения*/
	Exp * expTree;
};

/*приравнивание*/
class assigment : public operation {
protected:
	/*название то, к чему приравнивать*/
	std::string nameOfVal;
public:
	void calculate();
	std::string toCode(std::string & code) {
		auto codeName = expTree->init(nameOfVal, code);
		code += "fstp " + nameOfVal + "\n";
		return nameOfVal;
	}
	assigment(std::string line) : operation(line) {	}
};

/*вызов*/
class call : public operation {
public:
	call(std::string line) : operation(line) {
		auto indexBrk = line.find_first_of('(');
		auto tmp = line.substr(0, indexBrk);
		name = tmp.substr(tmp.find_last_of(' ') + 1);
	}
	void calculate();
	std::string toCode(std::string & code) {
		code += "";
		return code;
	}
};

/*вызов вывода*/
class printCall : public call {
public:
	printCall(std::string line) : call(line) {}

	std::string toCode(std::string & code) {
		code += lineOnOperation.substr(0, lineOnOperation.length() - 1);
		return "";
	}
};

/*break*/
class breakCall : public call {
public:
	breakCall(std::string line, cycleTree * treeCycle) : call(line) {
		this->treeCycle = treeCycle;
	}
	std::string toCode(std::string  &code);
	cycleTree * treeCycle;
};

/*continue*/
class continueCall : public call {
public:
	continueCall(std::string line, cycleTree * treeCycle) : call(line) {
		this->treeCycle = treeCycle;
	}
	std::string toCode(std::string  &code);
private:
	cycleTree * treeCycle;
};

