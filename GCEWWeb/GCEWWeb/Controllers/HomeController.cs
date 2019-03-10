using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using GCEWWeb.Models;
using Microsoft.Extensions.Options;
using GCEWWeb.Services;

namespace GCEWWeb.Controllers
{
    public class HomeController : Controller
    {
        public IOptions<CustomConfiguration> Options { get; set; }

        public HomeController(IOptions<CustomConfiguration> options)
        {
            Options = options ?? throw new ArgumentNullException(nameof(options));
            SiteTemplateInit.InitAllModules(Options.Value);
        }

        public IActionResult Test()
        {
            return View();
        }

        public IActionResult TestGraph()
        {
            return View();
        }

        public IActionResult Index()
        {
            ViewBag.Configuration = Options.Value;
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
