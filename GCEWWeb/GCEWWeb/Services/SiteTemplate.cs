using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services
{
    public class TemplateSite
    {
        public string Name { get; set; }
        public string Template { get; set; }
        public int Count { get; set; }
        public string[] Arguments { get; set; }
    }
    public class SiteTemplate
    {
        public CustomConfiguration CustomConfiguration { get; set; }

        public SiteTemplate(CustomConfiguration customConfiguration)
        {
            CustomConfiguration = customConfiguration ?? throw new ArgumentNullException(nameof(customConfiguration));
        }

        public Dictionary<string, TemplateSite> TemplateSites { get; set; }

        public Dictionary<string, TemplateSite> ReadListTemplates()
        {
            if (TemplateSites != null)
                return TemplateSites;
            TemplateSites = JsonConvert.DeserializeObject<List<TemplateSite>>(File.ReadAllText(CustomConfiguration.SiteTemplateFile))
                .ToDictionary(x => x.Name, x => x);
            return TemplateSites;
        }

        public TemplateSite this[string name]
        {
            get
            {
                var res = TemplateSites[name];
                if (res == null)
                    return ReadListTemplates()[name];
                return TemplateSites[name];
            }
        }
    }
}
