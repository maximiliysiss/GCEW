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
using GCEWWeb.Models.ControllerModels;

namespace GCEWWeb.Controllers
{
    [Authorize]
    public class HomeController : BaseController
    {
        public IViewRenderService ViewRenderService { get; set; }

        public HomeController(IOptions<CustomConfiguration> options, IViewRenderService viewRenderService, DatabaseContext databaseContext)
            : base(databaseContext, options.Value)
        {
            ViewRenderService = viewRenderService ?? throw new ArgumentNullException(nameof(viewRenderService));
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
        public IActionResult CreateProjectBy([FromForm]bool RedirectToProject)
        {
            ViewBag.RedirectToProject = RedirectToProject;
            return View("CreateProject");
        }

        [HttpPost]
        public IActionResult CreateProject(Project project, [FromForm]bool RedirectToProject)
        {
            project.DateTime = DateTime.Now;
            project.Path = $"{Options.GlobalProjectPathForUser(UserName)}{project.Name}";
            project.User = UserDatabase;
            DatabaseContext.Projects.Add(project);
            DatabaseContext.SaveChanges();
            Directory.CreateDirectory(project.Path);
            if (RedirectToProject)
                return RedirectToAction("OpenProject", "Home", new { idOpenProject = project.ID });
            return RedirectToAction("Projects", "Home");
        }

        [HttpPost]
        public IActionResult OpenProject(int idOpenProject)
        {
            ViewBag.Configuration = Options;
            ViewBag.RenderEngine = ViewRenderService;
            ViewBag.ProjectConfiguration = new ProjectConfiguration();
            var project = DatabaseContext.Projects.Find(idOpenProject);
            return View("Index", project);
        }

        [HttpPost]
        public IActionResult Save(SaveModel saveModel)
        {
            using (var file = new StreamWriter(new FileStream(saveModel.Path, FileMode.Truncate)))
                file.Write(saveModel.Data);
            return Ok();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
