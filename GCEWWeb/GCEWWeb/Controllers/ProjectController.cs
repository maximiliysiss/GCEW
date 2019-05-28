using System.IO;
using GCEWWeb.Models;
using GCEWWeb.Services;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Options;

namespace GCEWWeb.Controllers
{
    [Authorize]
    public class ProjectController : BaseController
    {
        public ProjectController(DatabaseContext databaseContext, IOptions<CustomConfiguration> options) : base(databaseContext, options.Value)
        {
        }

        [HttpPost]
        public string ProjectTree(int id)
        {
            return DatabaseContext.Projects.Find(id).FileSystemTreeJSON;
        }

        [HttpPost]
        public bool CreateFileInFolder(string path, string fileName, int id)
        {
            if (StringWorker.IsNullOrEmpty(path, fileName))
                return false;
            var pathNew = Path.Combine(path, fileName + ".graphic");
            if (System.IO.File.Exists(pathNew))
                pathNew = Path.Combine(path, fileName + "_new.graphic");
            System.IO.File.Create(pathNew).Close();
            return true;
        }

        [HttpPost]
        public bool AddNewFolder(string path, string fileName, int id)
        {
            if (StringWorker.IsNullOrEmpty(path, fileName))
                return false;
            var pathNew = Path.Combine(path, fileName);
            if (System.IO.Directory.Exists(pathNew))
                pathNew = Path.Combine(path, fileName + "_new");
            System.IO.Directory.CreateDirectory(pathNew);
            return true;
        }

        [HttpPost]
        public bool DeleteFolder(string name)
        {
            Directory.Delete(name, true);
            return true;
        }

        [HttpPost]
        public bool CreateFile(string name, int projectID)
        {
            var project = DatabaseContext.Projects.Find(projectID);
            if (project == null)
                return false;
            var path = Path.Combine(project.Path, name + ".graphic");
            if (System.IO.File.Exists(path))
                path = Path.Combine(project.Path, name + "_new.graphic");
            System.IO.File.Create(path).Close();
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

        [HttpPost]
        public bool Save(string name, string text, string link)
        {
            return true;
        }
    }
}
