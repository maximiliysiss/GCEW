using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using GCEWWeb.Services;
using Microsoft.AspNetCore.Mvc;

namespace GCEWWeb.Controllers
{
    public enum ElementType : int
    {
        Variable,
        For,
        While,
        If,
        Else,
        Function,
        Procedure,
        ChangeValue,
        Addition,
        Substract,
        Divide,
        Multiply
    }


    public class ConstructorController : Controller
    {

        [HttpPost]
        public string CreateNewElement([FromBody]ElementType elementType)
        {
            using (var stream = new System.IO.StreamReader(Request.Body))
            {
                var text = stream.ReadToEnd();
            }
            return ElementConstructor.GetBuilder(elementType)?.Html;
        }
    }
}