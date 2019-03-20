using GCEWWeb.Controllers;
using GCEWWeb.Services.Constructors;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services
{
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
                case ElementType.For:
                    break;
                case ElementType.While:
                    break;
                case ElementType.If:
                    break;
                case ElementType.Else:
                    break;
                case ElementType.Function:
                    break;
                case ElementType.Procedure:
                    break;
                case ElementType.ChangeValue:
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
            }
            return elem;
        }
    }
}
