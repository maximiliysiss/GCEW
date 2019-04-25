using GCEWWeb.Extenstions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace GCEWWeb.Services
{
    /// <summary>
    /// Resource
    /// </summary>
    public interface IResource
    {
        string Name { get; set; }
        /// <summary>
        /// Additional action for every element after loading to dictionary
        /// </summary>
        /// <param name="customConfiguration"></param>
        void ExtensionAction(CustomConfiguration customConfiguration);
    }

    /// <summary>
    /// Menu element
    /// </summary>
    [TemplateSiteClass("MenuElementRoot,MenuElement")]
    public class MenuElements : IResource
    {
        public string Name { get; set; }
        [TemplateSiteProperty("caption")]
        public string Caption { get; set; }
        [TemplateSiteProperty("function")]
        public string Function { get; set; }
        [TemplateSiteProperty("innermenu", TemplateType.Array)]
        public MenuElements[] InnerMenu { get; set; }

        public void ExtensionAction(CustomConfiguration customConfiguration) { }
    }
}
