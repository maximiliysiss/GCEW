using CommonLibrary.Compiler;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services.Constructors
{
    [TemplateSiteClass("ElementPrimitiveBool")]
    public abstract class ElementBool : ElementPrimitive
    {
        public ElementPrimitive True { get; set; }
        public ElementPrimitive False { get; set; }
    }


    public class ElementEqual : ElementBool
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "==";

        public override ElementType ElementType => ElementType.Equal;
    }

    public class ElementGreater : ElementBool
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => ">";

        public override ElementType ElementType => ElementType.Greater;
    }

    public class ElementLower : ElementBool
    {
        [TemplateSiteProperty("caption")]
        public override string Operation => "<";

        public override ElementType ElementType => ElementType.Lower;
    }
}
