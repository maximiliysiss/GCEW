using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services.Constructors
{
    [TemplateSiteClass("ElementVariable")]
    public class ElementVariable : IElement, INumberExpressionElement
    {
        public ElementVariable()
        {
            Caption = "Variable";
            Type = "Not Defined";
            Value = "Not Defined";
        }

        [TemplateSiteProperty("type")]
        public string Type { get; set; }
        [TemplateSiteProperty("value")]
        public string Value { get; set; }
        [TemplateSiteProperty("caption")]
        public string Caption { get; set; }
    }
}
