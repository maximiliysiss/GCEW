using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services.Constructors
{
    public abstract class IElement
    {
        public string Html => TemplateSerialize.Serialize(this);
    }
}
