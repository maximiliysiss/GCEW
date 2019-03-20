using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using GCEWWeb.Models;
using Microsoft.Extensions.Options;
using GCEWWeb.Services;
using GCEWWeb.Utilities;

namespace GCEWWeb.Controllers
{
    public class HomeController : Controller
    {
        public IOptions<CustomConfiguration> Options { get; set; }
        public IViewRenderService ViewRenderService { get; set; }
        public DatabaseContext DatabaseContext { get; set; }

        public HomeController(IOptions<CustomConfiguration> options, IViewRenderService viewRenderService, DatabaseContext databaseContext)
        {
            Options = options ?? throw new ArgumentNullException(nameof(options));
            ViewRenderService = viewRenderService ?? throw new ArgumentNullException(nameof(viewRenderService));
            databaseContext = databaseContext ?? throw new ArgumentException(nameof(databaseContext));
            SiteTemplateInit.InitAllModules(Options.Value);
        }

        public IActionResult Index()
        {
            ViewBag.Configuration = Options.Value;
            ViewBag.RenderEngine = ViewRenderService;
            return View();
        }

        public IActionResult Test()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
