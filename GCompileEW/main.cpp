#include <QCoreApplication>
#include <Tools/filter.h>
#include <iostream>
#include <compiler.h>
#include <Modules/lexanalysis.h>

int main(int argc, char *argv[])
{
    Compiler compiler;
    LexAnalysis lex(&compiler);
}
