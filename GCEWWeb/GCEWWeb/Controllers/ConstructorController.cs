using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using GCEWWeb.Services;
using GCEWWeb.Services.Constructors;
using Microsoft.AspNetCore.Mvc;

namespace GCEWWeb.Controllers
{
    public class ConstructorController : Microsoft.AspNetCore.Mvc.ControllerBase
    {

        [HttpPost]
        public IElement CreateNewElement(ElementType elementType)
        {
            return ElementConstructor.GetBuilder(elementType);
        }
    }
}