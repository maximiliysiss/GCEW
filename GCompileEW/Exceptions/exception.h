#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <string>

class Exception
{
public:
    Exception(std::string name);
    Exception(std::string name, std::string other);
    virtual std::string What() = 0;
protected:
    std::string name;

    std::string other;
};

#endif // EXCEPTION_H
