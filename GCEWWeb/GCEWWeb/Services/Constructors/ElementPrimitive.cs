using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services.Constructors
{
    [TemplateSiteClass("ElementPrimitive")]
    public abstract class ElementPrimitive : IElement
    {
        [TemplateSiteProperty("caption")]
        public abstract string Operation { get; }
        public List<ElementVariable> ElementVariables { get; set; } = new List<ElementVariable>();
    }

    public class ElementAddiction : ElementPrimitive
    {
        public override string Operation => "+";
    }

    public class ElementSubstract : ElementPrimitive
    {
        public override string Operation => "-";
    }

    public class ElementDivide : ElementPrimitive
    {
        public override string Operation => "/";
    }

    public class ElementMultiply : ElementPrimitive
    {
        public override string Operation => "*";
    }
}
