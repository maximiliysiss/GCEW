using GCEWWeb.Models;
using GCEWWeb.Models.Database;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Claims;
using System.Threading.Tasks;

namespace GCEWWeb.Controllers
{
    public abstract class BaseController : Controller
    {
        public int UserID => int.Parse(User.Claims.FirstOrDefault(x => x.Type == ClaimTypes.NameIdentifier).Value);
        public string UserName => User.Claims.FirstOrDefault(x => x.Type == ClaimTypes.Name).Value;
        public User UserDatabase => DatabaseContext.Users.FirstOrDefault(x => x.ID == UserID);

        public BaseController(DatabaseContext databaseContext)
        {
            DatabaseContext = databaseContext ?? throw new ArgumentNullException(nameof(databaseContext));
        }

        public DatabaseContext DatabaseContext { get; set; }
    }
}
