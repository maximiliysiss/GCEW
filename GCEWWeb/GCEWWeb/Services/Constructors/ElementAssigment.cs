using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services.Constructors
{
    [TemplateSiteClass("ElementAssigment")]
    public class ElementAssigment : IElement
    {
        public ElementVariable ElementVariable { get; set; }
        public IElement Assign { get; set; }
    }
}
