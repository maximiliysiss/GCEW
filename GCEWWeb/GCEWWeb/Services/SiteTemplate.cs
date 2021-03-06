﻿using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services
{
    /// <summary>
    /// Site's templates
    /// </summary>
    public class SiteTemplateInit
    {
        public static void InitAllModules(CustomConfiguration customConfiguration)
        {
            SiteTemplate<MenuElements>.Instance(customConfiguration, customConfiguration.MenuTemplate);
            SiteTemplate<TemplateSite>.Instance(customConfiguration, customConfiguration.SiteTemplateFile);
            SiteTemplate<ContextMenu>.Instance(customConfiguration, customConfiguration.ContextMenuTemplate);
            SiteTemplate<TemplateScript>.Instance(customConfiguration, customConfiguration.ScriptTemplateFile);
        }
    }

    /// <summary>
    /// 
    /// </summary>
    public class TemplateSite : IResource
    {
        public string Name { get; set; }
        public string Template { get; set; }
        public int Count { get; set; }
        public string[] Arguments { get; set; }

        public virtual void ExtensionAction(CustomConfiguration customConfiguration)
        {
            this.Template = File.ReadAllText($"{customConfiguration.SiteTemplatePath}{this.Name}.html");
        }
    }

    /// <summary>
    /// 
    /// </summary>
    public class TemplateScript : TemplateSite
    {
        public override void ExtensionAction(CustomConfiguration customConfiguration)
        {
            this.Template = File.ReadAllText($"{customConfiguration.ScriptTemplatePath}{this.Name}");
        }
    }

    /// <summary>
    /// Common class for Templates
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public class SiteTemplate<T> where T : class, IResource
    {
        /// <summary>
        /// Path for file
        /// </summary>
        private string path;
        /// <summary>
        /// Cashe
        /// </summary>
        private static SiteTemplate<T> siteTemplate;
        /// <summary>
        /// Configuration
        /// </summary>
        private CustomConfiguration customConfiguration;
        private SiteTemplate() { }
        /// <summary>
        /// Singleton
        /// </summary>
        /// <param name="customConfiguration"></param>
        /// <param name="path"></param>
        /// <returns></returns>
        public static SiteTemplate<T> Instance(CustomConfiguration customConfiguration, string path)
        {
            if (siteTemplate == null)
                siteTemplate = new SiteTemplate<T>(customConfiguration, path);
            if (siteTemplate.customConfiguration == null)
                siteTemplate.customConfiguration = customConfiguration;
            return siteTemplate;
        }
        /// <summary>
        /// Singleton
        /// </summary>
        /// <returns></returns>
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

        /// <summary>
        /// All templates
        /// </summary>
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
                if (TemplateSites.TryGetValue(name, out T val))
                    return val;
                return null;
            }
        }
    }
}
