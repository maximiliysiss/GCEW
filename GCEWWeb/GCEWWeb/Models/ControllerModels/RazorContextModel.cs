using GCEWWeb.Utilities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Models.ControllerModels
{
    public class RazorContextModel
    {
        public IViewRenderService ViewRenderService { get; set; }
        public object Model { get; set; }
    }
}
