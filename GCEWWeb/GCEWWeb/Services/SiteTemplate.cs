using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services
{
    public class SiteTemplateInit
    {
        public static void InitAllModules(CustomConfiguration customConfiguration)
        {
            SiteTemplate<ContextMenu>.Instance(customConfiguration, customConfiguration.ContextMenuTemplate);
            SiteTemplate<TemplateSite>.Instance(customConfiguration, customConfiguration.SiteTemplateFile);
        }
    }

    public class TemplateSite : IName
    {
        public string Name { get; set; }
        public string Template { get; set; }
        public int Count { get; set; }
        public string[] Arguments { get; set; }
    }
    public class SiteTemplate<T> where T : IName
    {
        private string path;
        private static SiteTemplate<T> siteTemplate;
        private SiteTemplate() { }
        public static SiteTemplate<T> Instance(CustomConfiguration customConfiguration, string path)
        {
            if (siteTemplate == null)
                siteTemplate = new SiteTemplate<T>(customConfiguration, path);
            return siteTemplate;
        }

        public static SiteTemplate<T> Instance()
        {
            if (siteTemplate == null)
                throw new NotSupportedException("Site Template not init");
            return siteTemplate;
        }

        public CustomConfiguration CustomConfiguration { get; set; }

        private SiteTemplate(CustomConfiguration customConfiguration, string path)
        {
            this.path = path;
            CustomConfiguration = customConfiguration ?? throw new ArgumentNullException(nameof(customConfiguration));
        }

        private Dictionary<string, T> templateSites;
        public Dictionary<string, T> TemplateSites
        {
            get
            {
                if (templateSites != null)
                    return templateSites;
                templateSites = JsonConvert.DeserializeObject<T[]>(File.ReadAllText(path))
                    .ToDictionary(x => x.Name, x => x);
                return templateSites;
            }
        }

        public T this[string name]
        {
            get
            {
                var res = TemplateSites[name];
                if (res == null)
                    return TemplateSites[name];
                return res;
            }
        }
    }
}
