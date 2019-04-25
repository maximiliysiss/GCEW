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

        public static FileSystemElement GetTree(this DirectoryInfo directoryInfo, int level = 0)
        {
            var listData = directoryInfo.EnumerateFiles("*.graphic").Select(x => new FileSystemElement
            {
                Caption = Path.GetFileNameWithoutExtension(x.Name),
                Tag = "file",
                Path = x.FullName
            }).ToList();
            listData.AddRange(directoryInfo.EnumerateDirectories().Select(x => x.GetTree(level + 1)));
            FileSystemElement fileSystem = new FileSystemElement
            {
                Caption = directoryInfo.Name,
                FileSystemElements = listData.ToArray(),
                Tag = level == 0 ? "" : "folder",
                Path = directoryInfo.FullName
            };
            return fileSystem;
        }

        public static FileSystemElementJSON GetTreeJSON(this DirectoryInfo directoryInfo, int level = 0)
        {
            var listData = directoryInfo.EnumerateFiles("*.graphic").Select(x => new FileSystemElementJSON
            {
                Caption = Path.GetFileNameWithoutExtension(x.Name),
                Tag = "file",
                Path = x.FullName
            }).ToList();
            listData.AddRange(directoryInfo.EnumerateDirectories().Select(x => x.GetTreeJSON(level + 1)));
            FileSystemElementJSON fileSystem = new FileSystemElementJSON
            {
                Caption = directoryInfo.Name,
                FileSystemElements = listData.ToArray(),
                Tag = level == 0 ? "" : "folder",
                Path = directoryInfo.FullName
            };
            return fileSystem;
        }

        public static string GetProject(this DirectoryInfo directoryInfo)
        {
            var root = new FileSystemElement
            {
                Caption = "Projects",
                FileSystemElements = directoryInfo.EnumerateDirectories().Select(x => new FileSystemElement
                {
                    Caption = x.Name,
                    Tag = "folder",
                    Path = directoryInfo.FullName
                }).ToArray()
            };
            return TemplateSerialize.SerializeScript(root);
        }

        public static string ToStringTree(this DirectoryInfo directoryInfo)
        {
            return TemplateSerialize.SerializeScript(directoryInfo.GetTree()).Replace("},]", "}]").Replace("\r\n", string.Empty)
                .Replace(", nodes: []", string.Empty).Replace("\\", "\\\\");
        }

        public static string ToJSONStringTree(this DirectoryInfo directoryInfo)
        {
            return TemplateSerialize.SerializeScript(directoryInfo.GetTreeJSON()).Replace("},]", "}]").Replace("\r\n", string.Empty)
                .Replace(", nodes: []", string.Empty).Replace("\\", "\\\\");
        }
    }
}
