#include "filenotfoundexception.h"

FileNotFoundException::FileNotFoundException(std::string name):Exception(name){}

FileNotFoundException::FileNotFoundException(std::string name, std::string other)
    :Exception(name,other){}

std::string FileNotFoundException::What(){
    return "File not found " + name + " in file" + other;
}
