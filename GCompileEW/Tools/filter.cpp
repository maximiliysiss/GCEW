#include "filter.h"

template<typename T, typename R>
Filter<T,R>::Filter(){}

template<typename T, typename R>
Filter<T,R>::Filter(T rule){
    this->rule = rule;
}

StringFilterByChar::StringFilterByChar():Filter(){}

StringFilterByChar::StringFilterByChar(std::string rule):Filter(rule){}

bool StringFilterByChar::operator ()(char value) const{
    return rule.find(value)!=std::string::npos;
}
