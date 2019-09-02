using GCEWWeb.Services;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.AspNetCore.Mvc.Routing;
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
            var headers = SiteTemplate<MenuElements>.Instance().TemplateSites.Select(x => x.Value);
            return GenerateMenuLevel(headers, replace: "<span class=\"space\"></span> <span> ► </span> </span> </a><ul class=\"dropdown-menu\"></ul>", replaceTo: "</span></a>");
        }

        private static string GenerateMenuLevel<T>(IEnumerable<T> contextMenus, bool isRoot = false, string replace = "", string replaceTo = "") where T : class
        {

            StringBuilder stringBuilder = new StringBuilder();
            foreach (var contextMenu in contextMenus)
                stringBuilder.Append(TemplateSerialize.Serialize(contextMenu).Replace("\r\n", string.Empty).Replace(replace, replaceTo));
            return stringBuilder.ToString();
        }

        public static string GenerateContextMenus(this IHtmlHelper htmlHelper)
        {
            var headers = SiteTemplate<ContextMenu>.Instance().TemplateSites.Select(x => x.Value);
            return GenerateMenuLevel(headers, replace: "<span class=\"space\"></span> <span> ► </span> <div class=\"menuContextRoot\"> <ul class=\"menuContextElements\"> </ul> </div>", replaceTo: string.Empty);
        }

        public static string AbsoluteAction(this IUrlHelper url, string actionName, string controllerName, object routeValues = null)
        {
            var httpContext = url.ActionContext.HttpContext;
            string scheme = httpContext.Request.Scheme;

            return url.Action(
                actionName,
                controllerName,
                routeValues,
                scheme
            );
        }
    }
}
