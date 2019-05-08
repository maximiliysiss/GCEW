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
    }

    public class ElementDivide : ElementPrimitive
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "/";
    }

    public class ElementMultiply : ElementPrimitive
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "*";
    }
}
