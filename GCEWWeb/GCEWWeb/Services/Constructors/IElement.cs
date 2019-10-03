using CommonLibrary.Compiler;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services.Constructors
{
    public interface INumberExpressionElement
    {

    }

    public abstract class IElement
    {
        [TemplateSiteProperty("id")]
        public string GUID { get; set; }
        public IElement()
        {
            GUID = Guid.NewGuid().ToString();
        }

        public void Copy(IElement element)
        {
            var props = element.GetType().GetProperties();
            foreach (var prop in props)
                prop.SetValue(this, prop.GetValue(element));
        }
        public string Html => TemplateSerialize.Serialize(this);
        public abstract ElementType ElementType { get; }
    }
}
