using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Models.Compiler
{
    public class CompilerSet
    {
        public Chain[] Chains { get; set; }
        public CompilerElement[] Vars { get; set; }
        public int ProjectId { get; set; }
    }
}
