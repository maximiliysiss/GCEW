#ifndef MODULE_H
#define MODULE_H


class Compiler;

class Module
{
private:
    Compiler * compiler;
public:
    Module(Compiler * compiler);
    Module();
    void SetCompiler(Compiler * compiler);
    virtual bool Start() = 0;

    virtual ~Module(){}
};

#endif // MODULE_H
