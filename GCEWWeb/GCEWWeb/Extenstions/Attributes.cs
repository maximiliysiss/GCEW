using GCEWWeb.Exceptions;
using GCEWWeb.Extenstions;
using GCEWWeb.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GCEWWeb.Extenstions
{
    public enum TemplateType
    {
        Default,
        Array
    }

    public enum FilterType
    {
        IsNull
    }
}

[AttributeUsage(AttributeTargets.Class)]
public class TemplateSiteClass : Attribute
{
    public TemplateSiteClass(string name)
    {
        Name = name;
    }

    public string Name { get; set; }

}

[AttributeUsage(AttributeTargets.Property)]
public class TemplateSiteProperty : Attribute
{
    public TemplateSiteProperty(string name, TemplateType templateType = TemplateType.Default)
    {
        TemplateType = templateType;
        Name = name;
    }

    public TemplateType TemplateType { get; set; }
    public string Name { get; set; }
}

public class TemplateSerialize
{
    public static string Serialize<T>(T elem) where T : class
    {
        if (!(Attribute.GetCustomAttribute(elem.GetType(), typeof(TemplateSiteClass)) is TemplateSiteClass templateSiteClass))
            throw new NotFoundException("Not found TemplateSiteClass in this element");
        var template = templateSiteClass.Name.Split(",").Select(x => SiteTemplate<TemplateSite>.Instance()[x]);
        return Elem(elem, template, templateSiteClass);
    }

    public static string SerializeScript<T>(T elem) where T : class
    {
        if (!(Attribute.GetCustomAttribute(elem.GetType(), typeof(TemplateSiteClass)) is TemplateSiteClass templateSiteClass))
            throw new NotFoundException("Not found TemplateSiteClass in this element");
        var template = templateSiteClass.Name.Split(",").Select(x => SiteTemplate<TemplateScript>.Instance()[x]);
        return Elem(elem, template, templateSiteClass);
    }

    public static string Elem<T>(T elem, IEnumerable<TemplateSite> templateSites, TemplateSiteClass siteClass, int level = 0, string preTemplate = "")
    {
        var props = elem.GetType().GetProperties().Where(x => x.GetCustomAttributes(typeof(TemplateSiteProperty), true).Count() > 0)
                .Select(x => new
                {
                    Prop = x,
                    Attr = x.GetCustomAttributes(typeof(TemplateSiteProperty), true).Cast<TemplateSiteProperty>().First()
                });
        string template = preTemplate;
        if (string.IsNullOrEmpty(template))
            template = (level >= templateSites.Count() ? templateSites.Last() : templateSites.ElementAt(level)).Template;
        foreach (var prop in props)
        {
            StringBuilder sb = new StringBuilder();
            bool isTemplateSiteClass;
            var value = prop.Prop.GetValue(elem);
            if (value == null)
            {
                template = template.Replace($"{{{prop.Attr.Name}}}", string.Empty);
                continue;
            }
            switch (prop.Attr.TemplateType)
            {
                case TemplateType.Default:
                    isTemplateSiteClass = value.GetType().GetCustomAttributes(typeof(TemplateSiteClass), true).Length > 0;
                    if (isTemplateSiteClass)
                        sb.Append(Elem(value as dynamic, templateSites, siteClass));
                    else
                        sb.Append(value.ToString());
                    break;
                case TemplateType.Array:
                    isTemplateSiteClass = value.GetType().GetElementType().GetCustomAttributes(typeof(TemplateSiteClass), true).Length > 0;
                    if (isTemplateSiteClass)
                    {
                        if (value is dynamic[] values)
                            foreach (var element in values)
                                sb.Append(Elem(element, templateSites, siteClass, level + 1));
                    }
                    else
                        sb.Append(string.Join(", ", (value as object[]).ToArray()));
                    break;
            }
            template = template.Replace($"{{{prop.Attr.Name}}}", sb.ToString());
        }
        return template;
    }
}

