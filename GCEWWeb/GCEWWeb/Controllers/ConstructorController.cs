using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using GCEWWeb.Services;
using Microsoft.AspNetCore.Mvc;

namespace GCEWWeb.Controllers
{
    public enum ElementType
    {
        Variable,
        For,
        While,
        If,
        Else,
        Function,
        Procedure,
        ChangeValue
    }


    public class ConstructorController : Controller
    {

        [HttpPost]
        public string CreateNewElement(ElementType elementType)
        {
            return ElementConstructor.GetBuilder(elementType).Html;
        }
    }
}