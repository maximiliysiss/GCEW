#include "lexanalysis.h"

char LexAnalysis::GetAnalogBkts(char symbol)
{
    switch(symbol){
    case '}':case '{':
        return symbol=='{'?'}':'{';
        break;
    case ')':case '(':
        return symbol=='('?')':'(';
        break;
    case '[':case ']':
        return symbol=='['?']':'[';
        break;
    case '<':case '>':
        return symbol=='<'?'>':'<';
        break;
    default:
        return ' ';
    }
}

std::vector<std::string> LexAnalysis::Analysis(std::string fileName){
    std::ifstream file(fileName);
    if(!file.is_open())
        throw FileNotFoundException(fileName);
    std::string text((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());

    BktFilter filter;

    std::string bkts;

    std::copy_if(text.begin(), text.end(), std::back_inserter(bkts), filter);

    return std::vector<std::string>();
}

bool LexAnalysis::BktsValid(std::string input)
{
    std::stack<char> stack;
    for(unsigned int i=0;i<input.length();i++){
        if(stack.empty())
            stack.push(input[i]);
        else
            if(stack.top()==GetAnalogBkts(input[i]))
                stack.pop();
            else
                stack.push(input[i]);
    }
    return stack.empty();
}

bool LexAnalysis::Start()
{
    return true;
}
