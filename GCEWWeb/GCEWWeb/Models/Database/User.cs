using GCEWWeb.Models.ControllerModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Models.Database
{
    public class User
    {
        public int ID { get; set; }
        public string Login { get; set; }
        public string Name { get; set; }
        public string PasswordHash { get; set; }
        public Plan Plan { get; set; }
    }
}
