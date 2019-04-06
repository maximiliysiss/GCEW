using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services
{
    [TemplateSiteClass("FileSystemTreeRoot.js,FileSystemElement.txt")]
    public class FileSystemElement
    {
        [TemplateSiteProperty("caption")]
        public string Caption { get; set; }
        [TemplateSiteProperty("innerElements", Extenstions.TemplateType.Array)]
        public FileSystemElement[] FileSystemElements { get; set; }
        [TemplateSiteProperty("tag")]
        public string Tag { get; set; }
    }
}
