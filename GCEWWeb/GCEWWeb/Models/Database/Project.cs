﻿using GCEWWeb.Extenstions;
using GCEWWeb.Models.Database;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
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
        public bool IsTask { get; set; }
        public User User { get; set; }
        [NotMapped]
        public string FileSystemTree
        {
            get
            {
                if (string.IsNullOrEmpty(Path))
                    return string.Empty;
                return new DirectoryInfo(Path).ToStringTree();
            }
        }
        [NotMapped]
        public string FileSystemTreeJSON
        {
            get
            {
                if (string.IsNullOrEmpty(Path))
                    return string.Empty;
                return new DirectoryInfo(Path).ToJSONStringTree();
            }
        }
    }
}
