using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Models.Database
{
    public enum PaySystem
    {
        Alipay,
        Amazon,
        American_Express,
        Bancontact,
        BCC,
        Bitcoin,
        Boleto,
        Carte_Bleue,
        Cirrus,
        Citi_Bank,
        Click_and_Buy,
        Delta,
        DineroMail,
        DinersClub,
        DirectDebit,
        Discover,
        DotPay,
        EBAY,
        ECO,
        Epay,
        EPS,
        Eway,
        GiroPay,
        HSBC,
        iDeal,
        JCB,
        Maestro_1,
        Maestro_2,
        OK_Pay,
        Payoneer,
        PayPal,
        PayPoint,
        Payza,
        Pick_n_Pay,
        PostePay,
        Przelewy24,
        Sage,
        Skrill,
        Switch1,
        Switch2,
        todoCash,
        Ukash,
        UnionPay,
        Verified_by_VISA,
        Visa,
        WebMoney,
        Western_Union,
        Wirecard,
        WorldPay,
        Yandex_Money
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
