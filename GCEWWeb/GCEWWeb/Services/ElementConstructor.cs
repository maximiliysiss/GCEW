using CommonLibrary.Utilities;
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
        Addiction,
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
        private static FactoryGenerator<IElement, object, ElementType> elementFactory;

        public static IElement GetBuilder(ElementType elementType)
        {
            if (elementFactory != null)
                return elementFactory.Build(elementType);

            elementFactory = new FactoryGenerator<IElement, object, ElementType>();
            elementFactory.AddFor(() => new ElementVariable()).Where(ElementType.Variable);
            elementFactory.AddFor(() => new ElementAddiction()).Where(ElementType.Addiction);
            elementFactory.AddFor(() => new ElementSubstract()).Where(ElementType.Substract);
            elementFactory.AddFor(() => new ElementDivide()).Where(ElementType.Divide);
            elementFactory.AddFor(() => new ElementMultiply()).Where(ElementType.Multiply);
            elementFactory.AddFor(() => new ElementEqual()).Where(ElementType.Equal);
            elementFactory.AddFor(() => new ElementGreater()).Where(ElementType.Greater);
            elementFactory.AddFor(() => new ElementLower()).Where(ElementType.Lower);
            elementFactory.AddFor(() => new ElementPrint()).Where(ElementType.Print);
            elementFactory.AddFor(() => new ElementStart()).Where(ElementType.Start);
            return elementFactory.Build(elementType);
        }
    }
}
