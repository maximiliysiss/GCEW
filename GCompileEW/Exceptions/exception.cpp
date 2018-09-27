#include "exception.h"

Exception::Exception(std::string name){
    this->name = name;
}

Exception::Exception(std::string name, std::string other){
    this->name = name;
    this->other = other;
}
