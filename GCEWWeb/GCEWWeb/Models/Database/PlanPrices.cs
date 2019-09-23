namespace GCEWWeb.Models.Database
{
    public enum Plan
    {
        Free,
        Minimum,
        Maximum
        /* Какие-то еще планы */
    }

    public class PlanPrices
    {
        public int ID { get; set; }
        public Plan Plan { get; set; }
        public double Price { get; set; }
    }
}
