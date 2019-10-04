using CommonLibrary.Compiler;
using GCEWWeb.Extenstions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LanguageTranslation.Compiler
{
    public abstract class GraphNode
    {
        protected bool isRender = false;
        public string ID { get; set; }
        public GraphNode NextAction { get; set; }
        public GraphNode PrevAction { get; set; }
        public List<GraphNode> InputValues { get; set; } = new List<GraphNode>();
        public List<GraphNode> OutputValues { get; set; } = new List<GraphNode>();
        public abstract string Render();
        public string Name { get; set; }
        public abstract ElementType ElementType { get; }

        protected GraphNode(string iD)
        {
            ID = iD;
        }
    }

    public class Start : GraphNode
    {
        public Start(string iD) : base(iD)
        {
        }

        public override ElementType ElementType => ElementType.GlobalStart;

        public override string Render()
        {
            StringBuilder stringBuilder = new StringBuilder();
            stringBuilder.AppendLine("void main(){");
            stringBuilder.Append(NextAction?.Render() ?? string.Empty);
            stringBuilder.AppendLine("}");
            return stringBuilder.ToString();
        }
    }

    public class Print : GraphNode
    {
        public Print(string iD) : base(iD)
        {
        }

        public override ElementType ElementType => ElementType.Print;

        public override string Render()
        {
            if (isRender)
                return string.Empty;
            isRender = true;
            StringBuilder stringBuilder = new StringBuilder();
            StringBuilder format = new StringBuilder();
            for (int i = 0; i < InputValues.Count; i++)
                format.Append("%f ");
            stringBuilder.AppendLine($@"pureasm
            {{
                    printf(""{format.ToString()}"", {string.Join(",", InputValues.Cast<Variable>().Select(x => $"var({x.Name})"))})
            }}
            {NextAction?.Render() ?? string.Empty}");
            return stringBuilder.ToString();
        }
    }

    public class Variable : GraphNode
    {
        public string Value { get; set; }
        public string Type { get; set; }

        public override ElementType ElementType => ElementType.Variable;

        public Variable(string iD, string type, string value, string name) : base(iD)
        {
            this.Value = value;
            this.Type = type;
            this.Name = name;

            if (!Value.Contains("."))
                Value = $"{Value}.0";
        }

        public override string Render()
        {
            if (isRender)
                return string.Empty;
            isRender = true;
            return $"double {Name} = {(string.IsNullOrEmpty(Value) ? "0.0" : Value)};\n";
        }
    }

    public class Operation : Variable
    {
        private readonly ElementType operation;

        public Operation(string ID, ElementType operation)
            : base(ID, "double", "0.0", Guid.NewGuid().ToIdString())
        {
            this.operation = operation;
            this.Name = $"a{this.ID}";
        }

        public override string Render()
        {
            if (isRender)
                return string.Empty;
            isRender = true;

            string oper = string.Empty;
            switch (operation)
            {
                case ElementType.Addiction:
                    oper = "+";
                    break;
                case ElementType.Divide:
                    oper = "/";
                    break;
                case ElementType.Multiply:
                    oper = "*";
                    break;
                case ElementType.Substract:
                    oper = "-";
                    break;
            }

            StringBuilder sb = new StringBuilder();
            InputValues.ForEach(x => sb.Append(x.Render()));

            return $"{sb.ToString()}double {Name} = {string.Join(oper, InputValues.OfType<Variable>().Select(x => x.Name))};\n{this.NextAction.Render()}";
        }
    }
}
