using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services.Constructors
{
    [TemplateSiteClass("ElementVariable")]
    public class ElementVariable : IElement
    {
        public string Type { get; set; }
        public string Value { get; set; }
    }
}
