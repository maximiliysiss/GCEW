using GCEWWeb.Extenstions;
using GCEWWeb.Models.Database;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Models.Database
{
    public class Project
    {
        public int ID { get; set; }
        public string Name { get; set; }
        public string Path { get; set; }
        public double Size { get; set; }
        public DateTime DateTime { get; set; }
        public User User { get; set; }
        public string FileSystemTree => new DirectoryInfo(Path).ToStringTree();
    }
}
