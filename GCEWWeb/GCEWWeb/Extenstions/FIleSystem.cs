using GCEWWeb.Services;
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

        public static FileSystemElement GetTree(this DirectoryInfo directoryInfo)
        {
            FileSystemElement fileSystem = new FileSystemElement
            {
                Caption = directoryInfo.Name,
                FileSystemElements = directoryInfo.EnumerateFiles().Select(x => new FileSystemElement { Caption = x.Name }).ToArray()
            };
            fileSystem.FileSystemElements.Concat(directoryInfo.EnumerateDirectories().Select(x => x.GetTree()));
            return fileSystem;
        }
    }
}
