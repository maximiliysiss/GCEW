using GCEWWeb.Extenstions;
using GCEWWeb.Models;
using GCEWWeb.Services;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Controllers
{
    [Authorize]
    public class MenuController : BaseController
    {
        public MenuController(DatabaseContext databaseContext, CustomConfiguration options) : base(databaseContext, options)
        {
        }

        public IActionResult OpenProject()
        {
            ViewBag.Config = new DirectoryInfo(Options.GlobalProjectPathForUser(UserName)).GetProject();
            return PartialView("OpenProjectFile");
        }

        public IActionResult OpenFiles(int id)
        {
            var project = DatabaseContext.Projects.Find(id);
            ViewBag.Config = new DirectoryInfo(project.Path).ToStringTree();
            return PartialView("OpenProjectFile");
        }

        public IActionResult CreateProject()
        {
            ViewBag.RedirectToProject = true;
            return RedirectToAction("CreateProject", "Home");
        }
    }
}
