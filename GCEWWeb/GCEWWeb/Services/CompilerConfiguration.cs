using System;
using System.Xml.Serialization;

namespace GCEWWeb.Services
{
    [Serializable]
    [XmlRoot("configuration")]
    public class CompilerConfiguration
    {
        [XmlAttribute("Libs")]
        public string LibraryPath { get; set; }
        [XmlAttribute("Compile")]
        public string CompilePath { get; set; }
    }
}