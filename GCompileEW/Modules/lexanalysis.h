#ifndef LEXANALYSIS_H
#define LEXANALYSIS_H
#include <vector>
#include <string>
#include <fstream>
#include "Exceptions/filenotfoundexception.h"
#include "Tools/filter.h"
#include "Modules/module.h"
#include <stack>



class LexAnalysis:public Module
{
private:

    char GetAnalogBkts(char symbol);

public:

    LexAnalysis():Module(){}

    LexAnalysis(Compiler * compiler):Module(compiler){}

    std::vector<std::string> Analysis(std::vector<std::string> fileNames);

    std::vector<std::string> Analysis(std::string fileName);

    bool BktsValid(std::string input);

    bool Start();
};

#endif // LEXANALYSIS_H
