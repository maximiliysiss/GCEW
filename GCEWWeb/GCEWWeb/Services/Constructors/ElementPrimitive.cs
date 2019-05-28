using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services.Constructors
{
    [TemplateSiteClass("ElementPrimitive")]
    public abstract class ElementPrimitive : IElement
    {
        [TemplateSiteProperty("outputID")]
        public string OuterID { get; set; } = Guid.NewGuid().ToString();
        public abstract string Operation { get; }
        public string Comment { get; set; }
        public virtual List<int> InputCount => new List<int> { -1 };
        public List<ElementVariable> ElementVariables { get; set; } = new List<ElementVariable>();
    }

    public class ElementAddiction : ElementPrimitive
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "+";
    }

    public class ElementSubstract : ElementPrimitive
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "-";
        public override List<int> InputCount => new List<int> { 1, -1 };
    }

    public class ElementDivide : ElementPrimitive
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "/";
        public override List<int> InputCount => new List<int> { 1, 1 };
    }

    public class ElementMultiply : ElementPrimitive
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "*";
    }

    public class ElementMod : ElementPrimitive
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "%";
        public override List<int> InputCount => new List<int> { 1, 1 };
    }

    public class ElementPower : ElementPrimitive
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "Power";
        public override List<int> InputCount => new List<int> { 1, 1 };
    }

    public class ElementSin : ElementPrimitive
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "sin";
        public override List<int> InputCount => new List<int> { 1, 1 };
    }

    public class ElementCos : ElementPrimitive
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "cos";
        public override List<int> InputCount => new List<int> { 1, 1 };
    }
}
