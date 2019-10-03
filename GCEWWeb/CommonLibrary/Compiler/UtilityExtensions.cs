using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Extenstions
{
    public static class UtilityExtensions
    {
        public static string ToIdString(this Guid guid)
        {
            var str = guid.ToString().Replace("-", string.Empty);
            if (char.IsDigit(str[0]))
                str = $"a{str}";
            return str;
        }

        public static string ToIdString(this string str)
        {
            if (char.IsDigit(str[0]))
                str = $"a{str}";
            return str.Replace("-", string.Empty);
        }
    }
}
