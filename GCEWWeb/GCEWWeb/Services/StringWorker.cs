﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Services
{
    /// <summary>
    /// String extensions
    /// </summary>
    public static class StringWorker
    {
        /// <summary>
        /// Remove all big whiteSpaces
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public static string NormalizeWhiteSpace(string input)
        {
            if (string.IsNullOrEmpty(input))
                return string.Empty;

            int current = 0;
            char[] output = new char[input.Length];
            bool skipped = false;

            foreach (char c in input.ToCharArray())
            {
                if (char.IsWhiteSpace(c))
                {
                    if (!skipped)
                    {
                        if (current > 0)
                            output[current++] = ' ';

                        skipped = true;
                    }
                }
                else
                {
                    skipped = false;
                    output[current++] = c;
                }
            }

            return new string(output, 0, current);
        }


        public static bool IsNullOrEmpty(params string[] strs)
        {
            return strs.All(x => string.IsNullOrEmpty(x.Trim()));
        }
    }
}
