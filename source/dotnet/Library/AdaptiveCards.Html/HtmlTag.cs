using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace HtmlTags
{
    public interface IHtmlTag
    {
        string ToString();
    }

    public class HtmlTag : IHtmlTag
    {
        public HtmlTag(string element)
        {
            this.Element = element;
        }

        public string Element { get; set; }


        public List<string> Classes { get; set; } = new List<string>();

        public Dictionary<string, string> Styles { get; set; } = new Dictionary<string, string>();

        public List<IHtmlTag> Children { get; set; } = new List<IHtmlTag>();

        public string Text { get; set; } = String.Empty;

        public Dictionary<string, string> Attributes { get; set; } = new Dictionary<string, string>();

        public HtmlTag AddClass(string className)
        {
            this.Classes.Add(className);
            return this;
        }

        public HtmlTag Append(HtmlTag child)
        {
            this.Children.Add(child);
            return this;
        }

        public HtmlTag Style(string name, string value)
        {
            if (value == null)
                Styles.Remove(name);
            else
                Styles[name] = value;
            return this;
        }

        public HtmlTag Attr(string name, string value)
        {
            if (value == null)
                this.Attributes.Remove(name);
            else
                this.Attributes[name] = value;
            return this;
        }

        public virtual string ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append($"<{this.Element} ");
            if (this.Classes.Any())
            {
                sb.Append($"class='{String.Join(" ", this.Classes)}' ");
            }

            foreach (var attr in this.Attributes)
            {
                sb.Append($"{attr.Key}='{WebUtility.HtmlEncode(attr.Value)} '");
            }

            if (this.Styles.Any())
            {
                sb.Append($"style='{String.Join(";", this.Styles.Select(kv => $"{kv.Key}: {kv.Value}"))};' ");
            }

            sb.AppendLine(">");

            if (this.Children.Any() || !String.IsNullOrEmpty(this.Text))
            {
                if (!String.IsNullOrEmpty(this.Text))
                    sb.AppendLine(WebUtility.HtmlEncode(this.Text));

                foreach (var child in this.Children)
                {
                    sb.AppendLine(child.ToString());
                }
            }
            sb.AppendLine($"</{this.Element}>");
            return sb.ToString();
        }
    }

    public class DivTag : HtmlTag
    {
        public DivTag() : base("div")
        {
        }
    }

    public class LinkTag : HtmlTag, IHtmlTag
    {
        public LinkTag(string title, string url, params string[] classes) : base("a")
        {
            if (!String.IsNullOrEmpty(title))
                this.Attributes.Add("title", title);
            if (!String.IsNullOrEmpty(url))
                this.Attributes.Add("url", url);
            if (classes != null)
            {
                foreach (var className in classes)
                    this.AddClass(className);
            }
        }
    }

    public class LiteralTag : IHtmlTag
    {
        public LiteralTag(string html)
        {
            this.Html = html;
        }
        public string Html { get; set; }

        public virtual string ToString()
        {
            return this.Html;
        }
    }

    public class TableTag : HtmlTag, IHtmlTag
    {
        public TableTag() : base("table")
        {

        }

        public TableRowTag AddBodyRow()
        {

            var row = new TableRowTag();
            this.Children.Add(row);
            return row;
        }

    }

    public class TableRowTag : HtmlTag
    {
        public TableRowTag() : base("tr")
        {

        }

        public TableCellTag AddCell()
        {
            var cell = new TableCellTag();
            this.Children.Add(cell);
            return cell;
        }
    }

    public class TableCellTag : HtmlTag
    {
        public TableCellTag() : base("td")
        {

        }
    }
}

