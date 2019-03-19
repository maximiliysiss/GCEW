using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace GCEWWeb.Extenstions
{
    public static class FIleSystem
    {
        public static long GetSize(this DirectoryInfo directoryInfo)
        {
            long totalSize = directoryInfo.EnumerateFiles()
                      .Sum(file => file.Length);
            totalSize += directoryInfo.EnumerateDirectories()
                         .Sum(dir => dir.GetSize());
            return totalSize;
        }
    }
}
