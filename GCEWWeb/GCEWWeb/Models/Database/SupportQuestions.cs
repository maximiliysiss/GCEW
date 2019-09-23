using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Models.Database
{
    public class SupportQuestions
    {
        public int ID { get; set; }
        public string Content { get; set; }
        public string Answer { get; set; }
        public User User { get; set; }
        public User Support { get; set; }
        public bool IsAnswered { get; set; }
    }
}
