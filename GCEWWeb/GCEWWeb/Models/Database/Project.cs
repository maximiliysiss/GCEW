﻿using GCEWWeb.Models.Database;
using System;
using System.Collections.Generic;
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
        public User User { get; set; }
    }
}
