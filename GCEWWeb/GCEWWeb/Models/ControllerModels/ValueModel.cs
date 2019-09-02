using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Models.ControllerModels
{
    public class ValueModel<T>
    {
        public T Value { get; set; }
    }
}
