using GCEWWeb.Controllers;
using GCEWWeb.Services.Constructors;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services
{
    public enum ElementType : int
    {
        Variable,
        Addition,
        Substract,
        Divide,
        Multiply,
        Equal,
        Greater,
        Lower,
        Print,
        Start
    }


    /// <summary>
    /// Factory for elements
    /// </summary>
    public class ElementConstructor
    {
        public static IElement GetBuilder(ElementType elementType)
        {
            IElement elem = null;
            switch (elementType)
            {
                case ElementType.Variable:
                    elem = new ElementVariable();
                    break;
                case ElementType.Addition:
                    elem = new ElementAddiction();
                    break;
                case ElementType.Substract:
                    elem = new ElementSubstract();
                    break;
                case ElementType.Divide:
                    elem = new ElementDivide();
                    break;
                case ElementType.Multiply:
                    elem = new ElementMultiply();
                    break;
                case ElementType.Equal:
                    elem = new ElementEqual();
                    break;
                case ElementType.Greater:
                    elem = new ElementGreater();
                    break;
                case ElementType.Lower:
                    elem = new ElementLower();
                    break;
                case ElementType.Print:
                    elem = new ElementPrint();
                    break;
                case ElementType.Start:
                    elem = new ElementStart();
                    break;
            }
            return elem;
        }
    }
}
