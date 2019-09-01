#pragma once
#ifndef INSTRUMENTS_H
#define INSTRUMENTS_H

#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <cctype>
#include <stack>
#include <algorithm>
#include <Windows.h>
#include "TreeRegularBuilder.h"
#pragma comment(lib, "Rpcrt4.lib")

namespace gcew::commons
{
	std::string ltrim(std::string str);
	std::string rtrim(std::string str);
	std::string trim(std::string str);
	void commentEraser(std::string &code, bool & status);
	void eraserRepeate(std::string& line, char symbol);
	std::string eraseSpaces(std::string line);
	std::vector<std::string> splitter(std::string line, char sep);
	std::vector<std::string> leftSplitter(std::string line, char sep);
	std::string codeCorrector(std::string code);
	std::list<size_t> findAllIndexes(std::string input, std::string substr);
	std::list<size_t> findAllIndexes(std::string input, char substr);
	std::list<size_t> findAllIndexesWithOffset(std::string input, std::string substr);
	std::list<size_t> findAllIndexesWithOffset(std::string input, char substr);
	bool isNumber(std::string str);
	bool isBracketCorrect(const std::string & str);
	void removeFromString(std::string & input, std::string remove);
	std::string createUniqueGUID();
	std::vector<std::string> getArguments(std::string line);
}

#endif // !INSTRUMENTS_H
