#ifndef COMPILER_H
#define COMPILER_H
#include <iostream>
#include <vector>
#include <Modules/module.h>
#include <algorithm>
#include <string>
#include <Exceptions/exception.h>

class Compiler
{
private:
    std::vector<Module*> modules;

    std::vector<std::string> files;

    std::string fileMain;

public:
    Compiler();

    bool Start(){
        try{
        std::for_each(modules.begin(), modules.end(), [](Module * module){ module->Start();});
        }
        catch(Exception * ex){
            std::cout<< ex->What();
            return false;
        }
        return true;
    }

    void AddModule(Module * module){
        modules.push_back(module);
    }

    void RemoveModule(Module * module){
        while(true){
            auto iter = std::find(modules.begin(), modules.end(), module);
            if(iter==modules.end())
                break;
            modules.erase(iter);
        }
    }
};

#endif // COMPILER_H
