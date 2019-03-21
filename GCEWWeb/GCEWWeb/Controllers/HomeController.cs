﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using GCEWWeb.Models;
using Microsoft.Extensions.Options;
using GCEWWeb.Services;
using GCEWWeb.Utilities;
using Microsoft.AspNetCore.Authorization;
using GCEWWeb.Models.Database;
using System.IO;
using GCEWWeb.Extenstions;

namespace GCEWWeb.Controllers
{
    [Authorize]
    public class HomeController : BaseController
    {
        public CustomConfiguration Options { get; set; }
        public IViewRenderService ViewRenderService { get; set; }

        public HomeController(IOptions<CustomConfiguration> options, IViewRenderService viewRenderService, DatabaseContext databaseContext)
            : base(databaseContext)
        {
            Options = options.Value ?? throw new ArgumentNullException(nameof(options));
            ViewRenderService = viewRenderService ?? throw new ArgumentNullException(nameof(viewRenderService));
            SiteTemplateInit.InitAllModules(Options);
        }

        public IActionResult Index()
        {
            ViewBag.Configuration = Options;
            ViewBag.RenderEngine = ViewRenderService;
            return View();
        }

        public IActionResult Projects()
        {
            var projects = DatabaseContext.Projects.Where(x => x.User.ID == UserID).ToList();
            foreach (var project in projects)
                project.Size = new DirectoryInfo(project.Path).GetSize();
            return View(projects);
        }

        public IActionResult CreateProject()
        {
            return View();
        }

        [HttpPost]
        public IActionResult CreateProject(Project project)
        {
            project.DateTime = DateTime.Now;
            project.Path = $"{Options.GlobalProjectPathForUser(UserName)}{project.Name}";
            project.User = UserDatabase;
            DatabaseContext.Projects.Add(project);
            DatabaseContext.SaveChanges();
            Directory.CreateDirectory(project.Path);
            return RedirectToAction("Projects", "Home");
        }

        [HttpPost]
        public IActionResult OpenProject(int idOpenProject)
        {
            ViewBag.Configuration = Options;
            ViewBag.RenderEngine = ViewRenderService;
            var project = DatabaseContext.Projects.Find(idOpenProject);
            return View("Index", project);
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