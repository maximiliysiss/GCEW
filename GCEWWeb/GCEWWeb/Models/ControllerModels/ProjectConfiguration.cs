using CommonLibrary.Compiler;
using GCEWWeb.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Models.ControllerModels
{
    public class ProjectConfiguration
    {
        public Dictionary<string, Dictionary<ElementType, string>> CarouselTypes;

        public ProjectConfiguration()
        {
            CarouselTypes = new Dictionary<string, Dictionary<ElementType, string>>
            {
                { "Common", Enum.GetValues(typeof(ElementType)).Cast<ElementType>().ToDictionary(x => x, x => x.ToString()) }
            };
        }
    }
}
