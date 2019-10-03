using System;
using System.Collections.Generic;
using System.Text;

namespace CommonLibrary.Compiler
{
    public enum ElementType : int
    {
        Variable,
        Addiction,
        Substract,
        Divide,
        Multiply,
        Equal,
        Greater,
        Lower,
        Print,
        Start,
        GlobalStart
    }
}
