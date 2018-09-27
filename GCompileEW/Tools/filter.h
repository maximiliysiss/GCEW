#ifndef FILTER_H
#define FILTER_H

#include <algorithm>
#include <iterator>

template<typename T, typename R>
class Filter:public std::unary_function<R,bool>
{
public:
    Filter();
    Filter(T rule);
    virtual bool operator()(R value) const = 0;
protected:
    T rule;
};


class StringFilterByChar : public Filter<std::string, char>{
public:
    StringFilterByChar();
    StringFilterByChar(std::string rule);
    bool operator()(char value) const;
};

class BktFilter:public StringFilterByChar{
public:
    BktFilter():StringFilterByChar("[]{}<>()"){}
};

#endif // FILTER_H
