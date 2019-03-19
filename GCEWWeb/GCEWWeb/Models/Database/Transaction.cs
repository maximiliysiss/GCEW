using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Models.Database
{
    public enum PaySystem
    {
        PayPal,
        Card,
        Qiwi
    }

    public class Transaction
    {
        public int ID { get; set; }
        public DateTime DateTime { get; set; }
        public User User { get; set; }
        [Required(ErrorMessage = "Pay system is Required")]
        public PaySystem PaySystem { get; set; }
        public Plan Plan { get; set; }
        public double TransactionAmount { get; set; }
    }
}
