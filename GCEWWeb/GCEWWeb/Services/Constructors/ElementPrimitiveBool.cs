using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services.Constructors
{
    public class ElementEqual : ElementPrimitive
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "==";
        public override List<int> InputCount => new List<int> { -1 };
    }

    public class ElementGreater : ElementPrimitive
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => ">";
        public override List<int> InputCount => new List<int> { 1, 1 };
    }

    public class ElementLower : ElementPrimitive
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "<";
        public override List<int> InputCount => new List<int> { 1, 1 };
    }
}
