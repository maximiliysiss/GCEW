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
        public IElement Prev { get; set; }
        public IElement Next { get; set; }
        public List<IElement> InputElements { get; set; } = new List<IElement>();
    }

    public class ElementAddiction : ElementPrimitive
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "+";
        public override ElementType ElementType => ElementType.Addition;
    }

    [TemplateSiteClass("ElementSubstract")]
    public class ElementSubstract : ElementPrimitive
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "-";
        public override ElementType ElementType => ElementType.Substract;
    }

    [TemplateSiteClass("ElementDivide")]
    public class ElementDivide : ElementPrimitive
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "/";
        public override ElementType ElementType => ElementType.Divide;
    }

    public class ElementMultiply : ElementPrimitive
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "*";
        public override ElementType ElementType => ElementType.Multiply;
    }
}
