using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services.Constructors
{
    [TemplateSiteClass("ElementPrint")]
    public class ElementPrint : IElement
    {
        public IElement Print { get; set; }
        public override ElementType ElementType => ElementType.Print;
    }
}
