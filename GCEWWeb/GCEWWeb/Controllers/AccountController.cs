using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Claims;
using System.Threading.Tasks;
using GCEWWeb.Models;
using GCEWWeb.Models.ControllerModels;
using GCEWWeb.Models.Database;
using GCEWWeb.Services;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Options;

namespace GCEWWeb.Controllers
{
    public class AccountController : BaseController
    {
        public AccountController(DatabaseContext databaseContext, IOptions<CustomConfiguration> options) : base(databaseContext, options.Value)
        {
        }

        private async void LoginAsync(User user)
        {
            var claims = new List<Claim>
                        {
                            new Claim(ClaimTypes.Name, user.Login),
                            new Claim(ClaimTypes.NameIdentifier, user.ID.ToString())
                        };
            ClaimsIdentity claimsIdentity = new ClaimsIdentity(claims, "ChatFurieLogin");
            ClaimsPrincipal claimsPrincipal = new ClaimsPrincipal(claimsIdentity);
            await HttpContext.SignInAsync(claimsPrincipal);
        }

        public IActionResult Login()
        {
            return View();
        }

        [HttpPost]
        public IActionResult Login(LoginModel loginModel)
        {
            if (ModelState.IsValid)
            {
                var user = DatabaseContext.Users.FirstOrDefault(x => x.Login == loginModel.Login && x.PasswordHash == CryptService.CreateMD5(loginModel.Password));
                if (user == null)
                {
                    ViewBag.Errors = "Incorrect User/Password";
                    return View(loginModel);
                }
                LoginAsync(user);
                return RedirectToAction("Projects", "Home");
            }
            return View(loginModel);
        }

        public IActionResult Register()
        {
            return View();
        }

        [HttpPost]
        public IActionResult Register(RegisterModel registerModel)
        {
            if (ModelState.IsValid)
                return View("SelectUserPlan", registerModel);
            return View(registerModel);
        }

        [Authorize]
        public IActionResult PayPage(Plan plan)
        {
            return View(new Transaction
            {
                TransactionAmount = DatabaseContext.PlanPrices.FirstOrDefault(x => x.Plan == plan).Price,
                DateTime = DateTime.Now
            });
        }

        [Authorize]
        [HttpPost]
        public IActionResult PayPage(Transaction transaction)
        {
            if (!ModelState.IsValid)
                return View(transaction);

            transaction.User = UserDatabase;
            DatabaseContext.Add(transaction);
            DatabaseContext.SaveChanges();

            return RedirectToAction("Projects", "Home");
        }

        [Authorize]
        [HttpPost]
        public IActionResult PayPageDecline(Transaction transaction)
        {
            return View();
        }

        [HttpPost]
        public IActionResult SelectUserPlanConfirmed(RegisterModel registerModel)
        {
            var plan = DatabaseContext.PlanPrices.FirstOrDefault(x => x.Plan == registerModel.Plan);

            var user = new User
            {
                Login = registerModel.Login,
                Name = registerModel.Nickname,
                PasswordHash = CryptService.CreateMD5(registerModel.Password),
                IsPayed = registerModel.Plan == Plan.Free,
                PlanPrices = plan
            };
            DatabaseContext.Users.Add(user);
            DatabaseContext.SaveChanges();
            LoginAsync(user);
            if (registerModel.Plan == Plan.Free)
                return RedirectToAction("Projects", "Home");
            return RedirectToAction("PayPage", "Account", registerModel.Plan);
        }

        public async Task<IActionResult> Logout()
        {
            await HttpContext.SignOutAsync(CookieAuthenticationDefaults.AuthenticationScheme);
            return RedirectToAction("Login", "Account");
        }
    }
}