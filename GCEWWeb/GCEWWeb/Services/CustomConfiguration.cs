using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services
{
    public class CustomConfiguration
    {
        public string SiteTemplateFile { get; set; }
        public string ContextMenuTemplate { get; set; }
        public string MenuTemplate { get; set; }
        public string SiteTemplatePath { get; set; }
        private string GlobalProjectPath { get; set; }
        public string ScriptTemplatePath { get; set; }
        public string ScriptTemplateFile { get; set; }
        public string GlobalProjectPathForUser(string name) => GlobalProjectPath.Replace("{name}", name);
    }
}
