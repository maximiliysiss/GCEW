using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using CommonLibrary.Compiler;
using GCEWWeb.Models.ControllerModels;
using GCEWWeb.Services;
using GCEWWeb.Services.Constructors;
using Microsoft.AspNetCore.Mvc;

namespace GCEWWeb.Controllers
{
    public class ConstructorController : Controller
    {

        [HttpPost]
        public IElement CreateNewElement(ValueModel<int> valueModel)
        {
            return ElementConstructor.GetBuilder((ElementType)valueModel.Value);
        }
    }
}