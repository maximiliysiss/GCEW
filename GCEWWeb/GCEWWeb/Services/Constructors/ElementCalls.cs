using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services.Constructors
{
    [TemplateSiteClass("ElementPrint")]
    public class ElementPrint : IElement
    {
        public IElement Prev { get; set; }
        public IElement Next { get; set; }
        public IElement Variable { get; set; }
        public override ElementType ElementType => ElementType.Print;
    }

    public class ElementStart : IElement
    {
        public IElement Prev { get; set; }
        public IElement Next { get; set; }
        public override ElementType ElementType => ElementType.Start;
    }
}
