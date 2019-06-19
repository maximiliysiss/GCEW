#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <deque>
#include <iostream>

#ifndef MATHPARSER_H

#include "Enums.h"
#include "instruments.h"

/*абстрактный узел дерева*/
class Exp {
public:
	/*напечтать информацию*/
	virtual void print() {}
	/*получить код*/
	virtual std::string code() = 0;
	/*проинициализировать переменные промежуточные*/
	virtual std::string init(std::string name, std::string &code) = 0;
	/*получить данные для сектора data*/
	virtual void getData(std::string & code) = 0;
	/*деструктор*/
	virtual ~Exp() {}
	/*получить код для дерева с bool логикой*/
	virtual std::vector<std::string> boolCode(std::string  & code, std::string out, std::string globalOut, std::string next) {
		return {};
	}
};

/*одноногий узел*/
class OneNode : public Exp {
	/*следующий*/
	Exp * next;
	/*операция*/
	char operation;
public:
	/*конструктор*/
	OneNode(Exp * next, char operation) {
		this->next = next;
		this->operation = operation;
	}
	/*код*/
	std::string code() {
		return "";
	}
	/*проинициализировать переменные*/
	std::string init(std::string name, std::string &code) {
		return "";
	}
	/*получить данные о переменных*/
	void getData(std::string & code) {

	}
	/*формировать bool код*/
	std::vector<std::string> boolCode(std::string  & code, std::string out, std::string globalOut, std::string next) {
		return  {};
	}
};

/*переменная / значение*/
class Term : public Exp {
	/*значение*/
	std::string val;
	/*имя*/
	std::string name;
public:
	Term(std::string v) :val(v) {}
	void getData(std::string & code) {
		if (isNumber(val)) {
			name = createUniqueGUID();
			code += name + " real8 " + val;
			if (val.find('.') == std::string::npos)
				code += ".0";
			code += "\n";
		}
		else
			name = val;
	}
	virtual std::string code() {
		return "\nfld " + name + "\n";
	}

	std::vector<std::string> boolCode(std::string  & codes, std::string out, std::string globalOut, std::string next) {
		codes += code();
		return { name };
	}

	void print() {
		std::cout << ' ' << val << ' ';
	}
	std::string init(std::string name, std::string &codes) {
		codes += code();
		return name;
	}
};

/*бинарный узел*/
class Node : public Exp {
	/*левая нога*/
	Exp *l_exp;
	/*правая нога*/
	Exp *r_exp;
	/*оперция*/
	char op; // +, -, *, /
	/*имя*/
	std::string name;
public:
	void getData(std::string & code) {
		name = createUniqueGUID();
		code += name + " real8 ?\n";
		l_exp->getData(code);
		r_exp->getData(code);
	}
	Node(char op, Exp* left, Exp* right) :op(op), l_exp(left), r_exp(right) {}
	~Node() {
		if (l_exp)
			delete l_exp;
		if (r_exp)
			delete r_exp;
	}
	void print() {
		std::cout << '(' << op << ' ';
		l_exp->print();
		r_exp->print();
		std::cout << ')';
	}
	std::string code() {
		std::string codeRes;
		return codeRes;
	}
	std::string init(std::string name, std::string &codes) {
		std::string code;
		auto f = l_exp->init(name, code);
		auto s = r_exp->init(name, code);

		switch (op) {
		case '+':
			code += "fadd\n";
			break;
		case '-':
			code += "fsub\n";
			break;
		case '/':
			code += "fdiv\n";
			break;
		case '*':
			code += "fmul\n";
			break;
		}

		codes += code;
		return name;
	}

	std::vector<std::string> boolCode(std::string  & code, std::string out, std::string globalOut, std::string next) {

		if (op == '>' || op == '<') {
			code += "startbool" + name + ":\n";
			auto first = l_exp->boolCode(code, name, globalOut, next);
			auto second = r_exp->boolCode(code, name, globalOut, next);
			auto indexLast = code.substr(0, code.length() - 1).find_last_of('\n');
			code.erase(indexLast);
			code += "\n";
			code += "fcom " + second[0] + "\nfstsw ax\nfwait\nsahf\n";
			if (op == '>')
				code += "ja outbool" + name + "\n";
			else
				code += "jb outbool" + name + "\n";
			code += "jmp outfalse" + name + "\n";
			code += "outbool" + name + ":\n";
			code += "outfalse" + name + ":\n";
			return { "startbool" + name, "outbool" + name + ":", "outfalse" + name + ":" };
		}


		auto first = l_exp->boolCode(code, name, globalOut, next);
		auto second = r_exp->boolCode(code, name, globalOut, next);

		if (op == '&') {
			code += "startbool" + name + ":\n";
			code += "jmp " + first[0] + "\n";
			int index = code.find(first[1]);
			code.insert(index + first[1].length(), "\njmp " + second[0] + "\n");
			index = code.find(first[2]);
			code.insert(index + first[2].length(), "\njmp outfalse" + name + "\n");
			int indexSec = code.find(second[1]);
			code.insert(indexSec + second[1].length(), "\njmp outbool" + name + "\n");
			indexSec = code.find(second[2]);
			code.insert(indexSec + second[2].length(), "\njmp outfalse" + name + "\n");
			code += "outbool" + name + ":\n";
			code += "outfalse" + name + ":\n";
			return { "startbool" + name, "outbool" + name + ":", "outfalse" + name + ":" };
		}

		if (op == '|') {
			code += "startbool" + name + ":\n";
			code += "jmp " + first[0] + "\n";
			int index = code.find(first[1]);
			code.insert(index + first[1].length(), "\njmp outbool" + name + "\n");
			index = code.find(first[2]);
			code.insert(index + first[2].length(), "\njmp " + second[0] + "\n");
			int indexSec = code.find(second[1]);
			code.insert(indexSec + second[1].length(), "\njmp outbool" + name + "\n");
			indexSec = code.find(second[2]);
			code.insert(indexSec + second[2].length(), "\njmp outfalse" + name + "\n");
			code += "outbool" + name + ":\n";
			code += "outfalse" + name + ":\n";
			return { "startbool" + name, "outbool" + name + ":", "outfalse" + name + ":" };
		}
		return {};
	}
};

/*парсер*/
class mathParser
{
public:
	/*математика*/
	Exp * MathPars(std::string);
	/*булевая логика*/
	Exp * BoolPars(std::string);
};

#endif // !MATHPARSER_H


