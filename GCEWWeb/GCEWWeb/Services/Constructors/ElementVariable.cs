using CommonLibrary.Compiler;
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
        }

        [TemplateSiteProperty("type")]
        public string Type { get; set; } = "int";
        [TemplateSiteProperty("value")]
        public string Value { get; set; } = "0";
        [TemplateSiteProperty("caption")]
        public string Caption { get; set; }

        public override ElementType ElementType => ElementType.Variable;
    }
}
