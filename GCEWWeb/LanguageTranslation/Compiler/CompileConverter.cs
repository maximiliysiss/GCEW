using CommonLibrary.Compiler;
using GCEWWeb.Extenstions;
using GCEWWeb.Models.Compiler;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;

namespace LanguageTranslation.Compiler
{
    public class CompileConverter
    {
        readonly CompilerSet compilerSet;

        public CompileConverter(CompilerSet compilerSet)
        {
            this.compilerSet = compilerSet;
            foreach (var v in compilerSet.Vars)
                v.ElementId = v.ElementId.ToIdString();
            foreach (var ch in compilerSet?.Chains ?? new Chain[0])
            {
                ch.From = ch.From.ToIdString();
                ch.To = ch.To.ToIdString();
            }
        }

        public string Compile(string compilerString, string pathProject)
        {
            List<GraphNode> graphNodes = new List<GraphNode>();

            foreach (var v in compilerSet.Vars)
            {
                var type = (ElementType)Enum.Parse(typeof(ElementType), v.Type);
                switch (type)
                {
                    case ElementType.GlobalStart:
                        graphNodes.Add(new Start(v.ElementId));
                        break;
                    case ElementType.Addiction:
                    case ElementType.Substract:
                    case ElementType.Divide:
                    case ElementType.Multiply:
                        graphNodes.Add(new Operation(v.ElementId, type));
                        break;
                    case ElementType.Variable:
                        graphNodes.Add(new Variable(v.ElementId, v.Value, v.TypeValue, v.ElementId));
                        break;
                    case ElementType.Print:
                        graphNodes.Add(new Print(v.ElementId));
                        break;
                }
            }

            foreach (var chain in compilerSet?.Chains ?? new Chain[0])
            {
                var from = graphNodes.FirstOrDefault(x => chain.From.Contains(x.ID));
                var to = graphNodes.FirstOrDefault(x => chain.To.Contains(x.ID));
                if (chain.Type == "true")
                    from.NextAction = to;
                else
                    to.InputValues.Add(from);
            }

            string code = graphNodes.FirstOrDefault(x => x.ElementType == ElementType.GlobalStart).Render();

            var path = $"{pathProject}\\building\\";

            if (!Directory.Exists(path))
                Directory.CreateDirectory(path);
            else
            {
                Directory.Delete(path, true);
                Directory.CreateDirectory(path);
            }

            using (var streamWriter = new StreamWriter($"{path}main.gcew"))
                streamWriter.Write(code);

            ExecuteCommand($"{compilerString} {Path.GetFullPath($"{path}main.gcew")}");

            if (!File.Exists(Path.GetFullPath($"{path}\\GCEWCompile\\build\\main_build.exe")))
                return string.Empty;
            return $"{path}\\GCEWCompile\\build\\main_build.exe";
        }

        void ExecuteCommand(string command)
        {
            int exitCode;
            ProcessStartInfo processInfo;
            Process process;

            processInfo = new ProcessStartInfo("cmd.exe", "/c " + command);
            processInfo.CreateNoWindow = true;
            processInfo.UseShellExecute = false;
            // *** Redirect the output ***
            processInfo.RedirectStandardError = true;
            processInfo.RedirectStandardOutput = true;

            process = Process.Start(processInfo);
            process.WaitForExit();

            // *** Read the streams ***
            // Warning: This approach can lead to deadlocks, see Edit #2
            string output = process.StandardOutput.ReadToEnd();
            string error = process.StandardError.ReadToEnd();

            exitCode = process.ExitCode;

            Console.WriteLine((string.IsNullOrEmpty(output) ? "(none)" : output));
            Console.WriteLine((string.IsNullOrEmpty(error) ? "(none)" : error));
            Console.WriteLine("ExitCode: " + exitCode.ToString(), "ExecuteCommand");
            process.Close();
        }
    }
}
