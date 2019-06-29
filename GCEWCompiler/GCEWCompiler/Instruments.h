#pragma once
#ifndef INSTRUMENTS_H
#define INSTRUMENTS_H

#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <cctype>
#include <algorithm>

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

}

#endif // !INSTRUMENTS_H
