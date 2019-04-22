using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using GCEWWeb.Models;
using GCEWWeb.Services;
using Microsoft.AspNetCore.Mvc;

namespace GCEWWeb.Controllers
{
    public class ProjectController : BaseController
    {
        public ProjectController(DatabaseContext databaseContext, CustomConfiguration options) : base(databaseContext, options)
        {
        }

        [HttpPost]
        public bool CreateFile(string name, int projectID)
        {
            var project = DatabaseContext.Projects.Find(projectID);
            if (project == null)
                return false;

            System.IO.File.Create(Path.Combine(project.Path, name, ".graphic")).Close();
            return true;
        }

        [HttpPost]
        public bool CopyFile(string name)
        {
            var fileName = Path.GetFileName(name).Split(".")[0];
            System.IO.File.Copy(name, Path.Combine(Path.GetDirectoryName(name), fileName, "New.graphic"));
            return true;
        }

        [HttpPost]
        public bool DeleteFile(string name)
        {
            System.IO.File.Delete(name);
            return true;
        }
    }
}
