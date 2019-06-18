#include "mathParser.h"


template<typename T>
bool inFind(T elem, std::initializer_list<T> cont)
{
	auto res = std::find(cont.begin(), cont.end(), elem);
	return res != cont.end();
}

template<typename T>
void push_top(std::stringstream & oss, T elem)
{
	oss.seekg(-1, oss.cur);
}

Exp * mathParser::MathPars(std::string math)
{
	int level = 0;
	for (int i = math.size() - 1; i >= 0; --i) {
		char c = math[i];
		if (c == ')') {
			++level;
			continue;
		}
		if (c == '(') {
			--level;
			continue;
		}
		if (level > 0) continue;
		if ((c == '+' || c == '-') && i != 0) {//if i==0 then s[0] is sign
			std::string left(math.substr(0, i));
			std::string right(math.substr(i + 1));
			return new Node(c, MathPars(left), MathPars(right));
		}
	}
	for (int i = math.size() - 1; i >= 0; --i) {
		char c = math[i];
		if (c == ')') {
			++level;
			continue;
		}
		if (c == '(') {
			--level;
			continue;
		}
		if (level > 0) continue;
		if (c == '*' || c == '/') {
			std::string left(math.substr(0, i));
			std::string right(math.substr(i + 1));
			return new Node(c, MathPars(left), MathPars(right));
		}
	}
	if (math[0] == '(') {
		for (int i = 0; i < math.size(); ++i) {
			if (math[i] == '(') {
				++level;
				continue;
			}
			if (math[i] == ')') {
				--level;
				if (level == 0) {
					std::string exp(math.substr(1, i - 1));
					return MathPars(exp);
				}
				continue;
			}
		}
	}
	else
		//case value
		return new Term(math);
	std::cerr << "Error:never execute point" << std::endl;
	return NULL;//never
}

Exp * mathParser::BoolPars(std::string math)
{
	int level = 0;
	for (int i = math.size() - 1; i >= 0; --i) {
		char c = math[i];

		if (c == '!') {
			return new OneNode(BoolPars(math.substr(1)), c);
		}

		if (c == ')') {
			++level;
			continue;
		}
		if (c == '(') {
			--level;
			continue;
		}
		if (level > 0) continue;
		if ((c == '<' || c == '>') && i != 0) {
			std::string left(math.substr(0, i));
			std::string right(math.substr(i + 1));
			return new Node(c, BoolPars(left), BoolPars(right));
		}
	}
	for (int i = math.size() - 1; i >= 0; --i) {
		char c = math[i];
		if (c == ')') {
			++level;
			continue;
		}
		if (c == '(') {
			--level;
			continue;
		}
		if (level > 0) continue;
		if (c == '|' || c == '&') {
			std::string left(math.substr(0, i));
			std::string right(math.substr(i + 1));
			return new Node(c, BoolPars(left), BoolPars(right));
		}
	}
	if (math[0] == '(') {
		for (int i = 0; i < math.size(); ++i) {
			if (math[i] == '(') {
				++level;
				continue;
			}
			if (math[i] == ')') {
				--level;
				if (level == 0) {
					std::string exp(math.substr(1, i - 1));
					return BoolPars(exp);
				}
				continue;
			}
		}
	}
	else
		return new Term(math);
	std::cerr << "Error:never execute point" << std::endl;
	return NULL;
}
