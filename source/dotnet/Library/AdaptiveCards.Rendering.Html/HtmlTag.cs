// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;

namespace AdaptiveCards.Rendering.Html
{
    public class HtmlTag
    {
        private readonly bool _allowSelfClose;

        public HtmlTag(string element, bool allowSelfClose = true)
        {
            _allowSelfClose = allowSelfClose;
            this.Element = element;
        }

        public string Element { get; set; }


        public List<string> Classes { get; set; } = new List<string>();

        public Dictionary<string, string> Styles { get; set; } = new Dictionary<string, string>();

        public List<HtmlTag> Children { get; set; } = new List<HtmlTag>();

        public string Text { get; set; }

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

        public HtmlTag SetInnerText(string text)
        {
            Text = text;
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

        public HtmlTag Attr(string name, Uri value)
        {
            if (value == null)
                this.Attributes.Remove(name);
            else
                this.Attributes[name] = value.ToString();
            return this;
        }

        public override string ToString()
        {
            if (string.IsNullOrEmpty(this.Element))
            {
                // When element doesn't exist, it indicates a text node.
                return WebUtility.HtmlEncode(this.Text);
            }

            StringBuilder sb = new StringBuilder();
            sb.Append($"<{this.Element}");
            if (this.Classes.Any())
            {
                sb.Append($" class='{WebUtility.HtmlEncode(String.Join(" ", this.Classes))}'");
            }

            foreach (var attr in this.Attributes)
            {
                sb.Append($" {attr.Key}='{WebUtility.HtmlEncode(attr.Value)}'");
            }

            if (this.Styles.Any())
            {
                sb.Append($" style='{String.Join(";", this.Styles.Select(kv => $"{WebUtility.HtmlEncode(kv.Key)}: {WebUtility.HtmlEncode(kv.Value)}"))};'");
            }

            if (this.Children.Any() || !String.IsNullOrEmpty(this.Text) || !_allowSelfClose)
            {
                sb.Append(">");

                if (!String.IsNullOrEmpty(this.Text))
                    sb.Append(WebUtility.HtmlEncode(this.Text));

                foreach (var child in this.Children)
                {
                    sb.Append(child.ToString());
                }

                sb.Append($"</{this.Element}>");
            }
            else
            {
                // No children, so just self-close the element.
                sb.Append("/>");
            }

            return sb.ToString();
        }
    }

    public class DivTag : HtmlTag
    {
        public DivTag() : base("div", false)
        {
        }
    }

    public class LinkTag : HtmlTag
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

    public class TableTag : HtmlTag
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
