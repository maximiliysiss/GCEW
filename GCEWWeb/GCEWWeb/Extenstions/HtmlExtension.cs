using GCEWWeb.Services;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GCEWWeb.Extenstions
{
    public static class HtmlExtension
    {
        public static string MenuContainerHtml(this IHtmlHelper htmlHelper)
        {
            var headers = SiteTemplate<ContextMenu>.Instance().TemplateSites.Select(x => x.Value);
            return GenerateMenuLevel(headers);
        }

        private static string GenerateMenuLevel(IEnumerable<ContextMenu> contextMenus, bool isRoot = false)
        {
            StringBuilder stringBuilder = new StringBuilder();
            foreach (var contextMenu in contextMenus)
                stringBuilder.Append(TemplateSerialize.Serialize(contextMenu).Replace("<span class=\"space\"></span><span>►</span></span></a><ul class=\"dropdown-menu\"></ul>", "</span></a>"));
            return stringBuilder.ToString();
        }
    }
}
