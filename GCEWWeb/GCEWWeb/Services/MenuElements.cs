using GCEWWeb.Extenstions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace GCEWWeb.Services
{
    public interface IName
    {
        string Name { get; set; }
    }

    [TemplateSiteClass("MenuElementRoot,MenuElement")]
    public class MenuElements : IName
    {
        public string Name { get; set; }
        [TemplateSiteProperty("caption")]
        public string Caption { get; set; }
        public string Function { get; set; }
        [TemplateSiteProperty("innermenu", TemplateType.Array)]
        public MenuElements[] InnerMenu { get; set; }
    }
}
