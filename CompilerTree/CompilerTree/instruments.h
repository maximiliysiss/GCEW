#pragma once
#include <algorithm>
#include <vector>
#include <fstream>
#include <cctype>
#include <iterator>
#include <sstream>
#include <rpc.h>
#include <Windows.h>
#include <regex>
#include "compilerInnerData.h"
#pragma comment(lib, "Rpcrt4.lib")

/*macros помощник для генерации указателя на функцию типа type*/
#define filterCustom(type) void (*filter)(##type &) 
/*создать уникальный идентификатор*/
std::string createUniqueGUID();
/*удалить пробелы слева*/
std::string ltrim(std::string str);
/*удалить пробелы справа*/
std::string rtrim(std::string str);
/*удалить проблеы со всех сторон*/
std::string trim(std::string str);
/*создать файл*/
void createFile(std::string fileName);
/*соединить все элементы от b до e в строку*/
template<typename T>
std::string join(T b, T e);
/*преобразовать данные листа в форма (|||) для регулярок*/
template<typename T>
std::string joinRegex(std::list<T>);
/*получить список типов дыннх в виде (|||)*/
std::string joinRegexTypes();
/*копировать файлы*/
void copyFiles(std::string from, std::string to);
/*использую разлделитель delimiter разделить строку на отдельные строки*/
std::vector<std::string> splitter(std::string input, char delimiter, filterCustom(std::string) = nullptr);
/*чилос ли эта строка*/
bool isNumber(std::string input);