using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using GCEWWeb.Models.ControllerModels;
using Microsoft.AspNetCore.Mvc;

namespace GCEWWeb.Controllers
{
    public class AccountController : Controller
    {
        public IActionResult Login()
        {
            return View();
        }

        [HttpPost]
        public async Task<IActionResult> Login(LoginModel loginModel)
        {
            return View();
        }

        public IActionResult Register()
        {
            return View();
        }

        [HttpPost]
        public async Task<IActionResult> Register(RegisterModel registerModel)
        {
            return View();
        }
    }
}