#include "module.h"

Module::Module()
{
    this->compiler= nullptr;
}

Module::Module(Compiler *compiler){
    this->compiler = compiler;
}

void Module::SetCompiler(Compiler *compiler){
    this->compiler = compiler;
}
