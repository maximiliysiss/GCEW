using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services.Constructors
{
    [TemplateSiteClass("ElementFunction")]
    public class ElementFunction : IElement, INumberExpressionElement
    {
        public string ReturnType { get; set; }
        public string Name { get; set; }
        public List<INumberExpressionElement> Arguments { get; set; }
    }
}
