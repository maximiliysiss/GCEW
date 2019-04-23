using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services
{
    /// <summary>
    /// Configuration for project
    /// </summary>
    public class CustomConfiguration
    {
        /// <summary>
        /// File with site's templates
        /// </summary>
        public string SiteTemplateFile { get; set; }
        /// <summary>
        /// Path for file with ContextMenu templates
        /// </summary>
        public string ContextMenuTemplate { get; set; }
        /// <summary>
        /// Path for file with Menu templates
        /// </summary>
        public string MenuTemplate { get; set; }
        /// <summary>
        /// Path for folder with templates
        /// </summary>
        public string SiteTemplatePath { get; set; }
        /// <summary>
        /// Folder for projects (local)
        /// </summary>
        public string GlobalProjectPath { get; set; }
        /// <summary>
        /// Path for file with script's templates
        /// </summary>
        public string ScriptTemplatePath { get; set; }
        /// <summary>
        /// Folder for scripts
        /// </summary>
        public string ScriptTemplateFile { get; set; }
        /// <summary>
        /// Get users path to projects
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public string GlobalProjectPathForUser(string name) => GlobalProjectPath.Replace("{name}", name);
    }
}
