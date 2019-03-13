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
            SiteTemplate<MenuElements>.Instance(customConfiguration, customConfiguration.MenuTemplate);
            SiteTemplate<TemplateSite>.Instance(customConfiguration, customConfiguration.SiteTemplateFile);
            SiteTemplate<ContextMenu>.Instance(customConfiguration, customConfiguration.ContextMenuTemplate);
        }
    }

    public class TemplateSite : IResource
    {
        public string Name { get; set; }
        public string Template { get; set; }
        public int Count { get; set; }
        public string[] Arguments { get; set; }

        public void ExtensionAction(CustomConfiguration customConfiguration)
        {
            this.Template = File.ReadAllText($"{customConfiguration.SiteTemplatePath}{this.Name}.html");
        }
    }
    public class SiteTemplate<T> where T : IResource
    {
        private string path;
        private static SiteTemplate<T> siteTemplate;
        private CustomConfiguration customConfiguration;
        private SiteTemplate() { }
        public static SiteTemplate<T> Instance(CustomConfiguration customConfiguration, string path)
        {
            if (siteTemplate == null)
                siteTemplate = new SiteTemplate<T>(customConfiguration, path);
            if (siteTemplate.customConfiguration == null)
                siteTemplate.customConfiguration = customConfiguration;
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
                foreach (var temp in templateSites)
                    temp.Value.ExtensionAction(customConfiguration);
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
