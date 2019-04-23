using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services
{
    /// <summary>
    /// Context menu
    /// </summary>
    [TemplateSiteClass("ContextMenuRoot,MenuElementContext")]
    public class ContextMenu : IResource
    {
        [TemplateSiteProperty("name")]
        public string Name { get; set; }
        [TemplateSiteProperty("caption")]
        public string Caption { get; set; }
        [TemplateSiteProperty("innermenu", Extenstions.TemplateType.Array)]
        public ContextMenu[] InnerMenu { get; set; }
        [TemplateSiteProperty("function")]
        public string Function { get; set; }

        public void ExtensionAction(CustomConfiguration customConfiguration) { }
    }
}
