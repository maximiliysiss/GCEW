using GCEWWeb.Models.Database;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Models.ControllerModels
{


    public class RegisterModel
    {
        [Required(ErrorMessage = "Login is required")]
        [DataType(DataType.EmailAddress, ErrorMessage = "This is not email")]
        public string Login { get; set; }
        [Required(ErrorMessage = "Nickname is required")]
        public string Nickname { get; set; }
        [Required(ErrorMessage = "Password is requried")]
        [DataType(DataType.Password)]
        [MinLength(6, ErrorMessage = "Min Length is 6")]
        public string Password { get; set; }
        [Required(ErrorMessage = "Password is requried")]
        [DataType(DataType.Password)]
        [MinLength(6, ErrorMessage = "Min Length is 6")]
        [Compare("Password", ErrorMessage = "Password != Confirmed Password")]
        public string ConfirmedPassword { get; set; }
        [Required(ErrorMessage = "Plan is required")]
        public Plan Plan { get; set; } = Plan.Free;
    }
}
