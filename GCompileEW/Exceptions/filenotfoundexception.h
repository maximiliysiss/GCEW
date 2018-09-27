#ifndef FILENOTFOUNDEXCEPTION_H
#define FILENOTFOUNDEXCEPTION_H
#include "Exceptions/exception.h"
#include <string>
class FileNotFoundException : public Exception
{
public:
    FileNotFoundException();
    FileNotFoundException(std::string name);
    FileNotFoundException(std::string name, std::string other);

    std::string What();
};

#endif // FILENOTFOUNDEXCEPTION_H
