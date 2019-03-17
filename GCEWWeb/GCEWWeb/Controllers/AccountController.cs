using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using GCEWWeb.Models;
using GCEWWeb.Models.ControllerModels;
using Microsoft.AspNetCore.Mvc;

namespace GCEWWeb.Controllers
{
    public class AccountController : Controller
    {
        public AccountController(DatabaseContext databaseContext)
        {
            DatabaseContext = databaseContext ?? throw new ArgumentNullException(nameof(databaseContext));
        }

        public DatabaseContext DatabaseContext { get; set; }


        public IActionResult Login()
        {
            return View();
        }

        [HttpPost]
        public async Task<IActionResult> Login(LoginModel loginModel)
        {
            return RedirectToAction("Index", "Home");
        }

        public IActionResult Register()
        {
            return View();
        }

        [HttpPost]
        public async Task<IActionResult> Register(RegisterModel registerModel)
        {
            return RedirectToAction("Index", "Home");
        }

        public IActionResult PayPage()
        {
            return View();
        }

        [HttpPost]
        public IActionResult PayPage(int id)
        {
            return View();
        }

        public IActionResult SelectUserPlan()
        {
            return View();
        }

        [HttpPost]
        public IActionResult SelectUserPlan(int id)
        {
            return View();
        }
    }
}