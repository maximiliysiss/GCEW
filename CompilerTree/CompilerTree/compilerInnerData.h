#pragma once
#include <list>
#include <string>
#include <map>
/*
	Данные системы
*/
class compilerInnerData
{
public:
	/*Типы данных*/
	static std::list<std::string> dataTypes;
	/*зарезервированные слова*/
	static std::map<std::string, std::string> reserverdWord;
};

