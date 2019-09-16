// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace AdaptiveCards.Rendering.Html.Test
{
    [TestClass]
    public class MarkdownToHtmlTagConverterTests
    {
        [TestMethod]
        public void BasicString()
        {
            List<HtmlTag> tags = MarkdownToHtmlTagConverter.Convert("hello world <>!@#$%^&*()/\\").ToList();

            Assert.AreEqual(1, tags.Count);

            Assert.AreEqual("p", tags[0].Element);
            Assert.AreEqual(null, tags[0].Text);
            Assert.AreEqual(1, tags[0].Children.Count);
            Assert.AreEqual(0, tags[0].Classes.Count);
            Assert.AreEqual(0, tags[0].Attributes.Count);
            Assert.AreEqual(0, tags[0].Styles.Count);

            Assert.AreEqual(null, tags[0].Children[0].Element);
            Assert.AreEqual("hello world <>!@#$%^&*()/\\", tags[0].Children[0].Text);
            Assert.AreEqual(0, tags[0].Children[0].Children.Count);
            Assert.AreEqual(0, tags[0].Children[0].Classes.Count);
            Assert.AreEqual(0, tags[0].Children[0].Attributes.Count);
            Assert.AreEqual(0, tags[0].Children[0].Styles.Count);

            var fullHtml = string.Join(string.Empty, tags);
            Assert.AreEqual("<p>hello world &lt;&gt;!@#$%^&amp;*()/\\</p>", fullHtml);
        }

        [TestMethod]
        public void ParagraphBreak()
        {
            List<HtmlTag> tags = MarkdownToHtmlTagConverter.Convert("hello\n\nworld").ToList();

            Assert.AreEqual(2, tags.Count);

            Assert.AreEqual("p", tags[0].Element);
            Assert.AreEqual(null, tags[0].Text);
            Assert.AreEqual(1, tags[0].Children.Count);
            Assert.AreEqual(0, tags[0].Classes.Count);
            Assert.AreEqual(0, tags[0].Attributes.Count);
            Assert.AreEqual(0, tags[0].Styles.Count);

            Assert.AreEqual(null, tags[0].Children[0].Element);
            Assert.AreEqual("hello", tags[0].Children[0].Text);
            Assert.AreEqual(0, tags[0].Children[0].Children.Count);
            Assert.AreEqual(0, tags[0].Children[0].Classes.Count);
            Assert.AreEqual(0, tags[0].Children[0].Attributes.Count);
            Assert.AreEqual(0, tags[0].Children[0].Styles.Count);

            Assert.AreEqual("p", tags[1].Element);
            Assert.AreEqual(null, tags[1].Text);
            Assert.AreEqual(1, tags[1].Children.Count);
            Assert.AreEqual(0, tags[1].Classes.Count);
            Assert.AreEqual(0, tags[1].Attributes.Count);
            Assert.AreEqual(0, tags[1].Styles.Count);

            Assert.AreEqual(null, tags[1].Children[0].Element);
            Assert.AreEqual("world", tags[1].Children[0].Text);
            Assert.AreEqual(0, tags[1].Children[0].Children.Count);
            Assert.AreEqual(0, tags[1].Children[0].Classes.Count);
            Assert.AreEqual(0, tags[1].Children[0].Attributes.Count);
            Assert.AreEqual(0, tags[1].Children[0].Styles.Count);

            var fullHtml = string.Join(string.Empty, tags);
            Assert.AreEqual("<p>hello</p><p>world</p>", fullHtml);
        }

        [TestMethod]
        public void BoldAndItalics()
        {
            List<HtmlTag> tags = MarkdownToHtmlTagConverter.Convert("normal1 *italic* normal2 **bold** normal3").ToList();

            Assert.AreEqual(1, tags.Count);

            Assert.AreEqual("p", tags[0].Element);
            Assert.AreEqual(null, tags[0].Text);
            Assert.AreEqual(5, tags[0].Children.Count);
            Assert.AreEqual(0, tags[0].Classes.Count);
            Assert.AreEqual(0, tags[0].Attributes.Count);
            Assert.AreEqual(0, tags[0].Styles.Count);

            Assert.AreEqual(null, tags[0].Children[0].Element);
            Assert.AreEqual("normal1 ", tags[0].Children[0].Text);
            Assert.AreEqual(0, tags[0].Children[0].Children.Count);
            Assert.AreEqual(0, tags[0].Children[0].Classes.Count);
            Assert.AreEqual(0, tags[0].Children[0].Attributes.Count);
            Assert.AreEqual(0, tags[0].Children[0].Styles.Count);

            Assert.AreEqual("em", tags[0].Children[1].Element);
            Assert.AreEqual(null, tags[0].Children[1].Text);
            Assert.AreEqual(1, tags[0].Children[1].Children.Count);
            Assert.AreEqual(0, tags[0].Children[1].Classes.Count);
            Assert.AreEqual(0, tags[0].Children[1].Attributes.Count);
            Assert.AreEqual(0, tags[0].Children[1].Styles.Count);

            Assert.AreEqual(null, tags[0].Children[1].Children[0].Element);
            Assert.AreEqual("italic", tags[0].Children[1].Children[0].Text);
            Assert.AreEqual(0, tags[0].Children[1].Children[0].Children.Count);
            Assert.AreEqual(0, tags[0].Children[1].Children[0].Classes.Count);
            Assert.AreEqual(0, tags[0].Children[1].Children[0].Attributes.Count);
            Assert.AreEqual(0, tags[0].Children[1].Children[0].Styles.Count);

            Assert.AreEqual(null, tags[0].Children[2].Element);
            Assert.AreEqual(" normal2 ", tags[0].Children[2].Text);
            Assert.AreEqual(0, tags[0].Children[2].Children.Count);
            Assert.AreEqual(0, tags[0].Children[2].Classes.Count);
            Assert.AreEqual(0, tags[0].Children[2].Attributes.Count);
            Assert.AreEqual(0, tags[0].Children[2].Styles.Count);

            Assert.AreEqual("strong", tags[0].Children[3].Element);
            Assert.AreEqual(null, tags[0].Children[3].Text);
            Assert.AreEqual(1, tags[0].Children[3].Children.Count);
            Assert.AreEqual(0, tags[0].Children[3].Classes.Count);
            Assert.AreEqual(0, tags[0].Children[3].Attributes.Count);
            Assert.AreEqual(0, tags[0].Children[3].Styles.Count);

            Assert.AreEqual(null, tags[0].Children[3].Children[0].Element);
            Assert.AreEqual("bold", tags[0].Children[3].Children[0].Text);
            Assert.AreEqual(0, tags[0].Children[3].Children[0].Children.Count);
            Assert.AreEqual(0, tags[0].Children[3].Children[0].Classes.Count);
            Assert.AreEqual(0, tags[0].Children[3].Children[0].Attributes.Count);
            Assert.AreEqual(0, tags[0].Children[3].Children[0].Styles.Count);

            Assert.AreEqual(null, tags[0].Children[4].Element);
            Assert.AreEqual(" normal3", tags[0].Children[4].Text);
            Assert.AreEqual(0, tags[0].Children[4].Children.Count);
            Assert.AreEqual(0, tags[0].Children[4].Classes.Count);
            Assert.AreEqual(0, tags[0].Children[4].Attributes.Count);
            Assert.AreEqual(0, tags[0].Children[4].Styles.Count);

            var fullHtml = string.Join(string.Empty, tags);
            Assert.AreEqual("<p>normal1 <em>italic</em> normal2 <strong>bold</strong> normal3</p>", fullHtml);
        }

        [TestMethod]
        public void Link()
        {
            List<HtmlTag> tags = MarkdownToHtmlTagConverter.Convert("[Bing](https://www.bing.com/)").ToList();

            Assert.AreEqual(1, tags.Count);

            Assert.AreEqual("p", tags[0].Element);
            Assert.AreEqual(null, tags[0].Text);
            Assert.AreEqual(1, tags[0].Children.Count);
            Assert.AreEqual(0, tags[0].Classes.Count);
            Assert.AreEqual(0, tags[0].Attributes.Count);
            Assert.AreEqual(0, tags[0].Styles.Count);

            Assert.AreEqual("a", tags[0].Children[0].Element);
            Assert.AreEqual(null, tags[0].Children[0].Text);
            Assert.AreEqual(1, tags[0].Children[0].Children.Count);
            Assert.AreEqual(0, tags[0].Children[0].Classes.Count);
            Assert.AreEqual(1, tags[0].Children[0].Attributes.Count);
            Assert.AreEqual(true, tags[0].Children[0].Attributes.ContainsKey("href"));
            Assert.AreEqual("https://www.bing.com/", tags[0].Children[0].Attributes["href"]);
            Assert.AreEqual(0, tags[0].Children[0].Styles.Count);

            Assert.AreEqual(null, tags[0].Children[0].Children[0].Element);
            Assert.AreEqual("Bing", tags[0].Children[0].Children[0].Text);
            Assert.AreEqual(0, tags[0].Children[0].Children[0].Children.Count);
            Assert.AreEqual(0, tags[0].Children[0].Children[0].Classes.Count);
            Assert.AreEqual(0, tags[0].Children[0].Children[0].Attributes.Count);
            Assert.AreEqual(0, tags[0].Children[0].Children[0].Styles.Count);

            var fullHtml = string.Join(string.Empty, tags);
            Assert.AreEqual("<p><a href='https://www.bing.com/'>Bing</a></p>", fullHtml);
        }

        [TestMethod]
        public void HorizontalRule()
        {
            List<HtmlTag> tags = MarkdownToHtmlTagConverter.Convert("text\n*********\ntext").ToList();

            Assert.AreEqual(3, tags.Count);

            Assert.AreEqual("p", tags[0].Element);
            Assert.AreEqual(null, tags[0].Text);
            Assert.AreEqual(1, tags[0].Children.Count);
            Assert.AreEqual(0, tags[0].Classes.Count);
            Assert.AreEqual(0, tags[0].Attributes.Count);
            Assert.AreEqual(0, tags[0].Styles.Count);

            Assert.AreEqual(null, tags[0].Children[0].Element);
            Assert.AreEqual("text", tags[0].Children[0].Text);
            Assert.AreEqual(0, tags[0].Children[0].Children.Count);
            Assert.AreEqual(0, tags[0].Children[0].Classes.Count);
            Assert.AreEqual(0, tags[0].Children[0].Attributes.Count);
            Assert.AreEqual(0, tags[0].Children[0].Styles.Count);

            Assert.AreEqual("hr", tags[1].Element);
            Assert.AreEqual(null, tags[1].Text);
            Assert.AreEqual(0, tags[1].Children.Count);
            Assert.AreEqual(0, tags[1].Classes.Count);
            Assert.AreEqual(0, tags[1].Attributes.Count);
            Assert.AreEqual(0, tags[1].Styles.Count);

            Assert.AreEqual("p", tags[2].Element);
            Assert.AreEqual(null, tags[2].Text);
            Assert.AreEqual(1, tags[2].Children.Count);
            Assert.AreEqual(0, tags[2].Classes.Count);
            Assert.AreEqual(0, tags[2].Attributes.Count);
            Assert.AreEqual(0, tags[2].Styles.Count);

            Assert.AreEqual(null, tags[2].Children[0].Element);
            Assert.AreEqual("text", tags[2].Children[0].Text);
            Assert.AreEqual(0, tags[2].Children[0].Children.Count);
            Assert.AreEqual(0, tags[2].Children[0].Classes.Count);
            Assert.AreEqual(0, tags[2].Children[0].Attributes.Count);
            Assert.AreEqual(0, tags[2].Children[0].Styles.Count);

            var fullHtml = string.Join(string.Empty, tags);
            Assert.AreEqual("<p>text</p><hr/><p>text</p>", fullHtml);
        }

        [TestMethod]
        public void ClassAttributeSetCorrectly()
        {
            // Using triple back ticks because it's the only place I can find in Marked.Net where the output HTML includes a class name.
            List<HtmlTag> tags = MarkdownToHtmlTagConverter.Convert("```CSharp\nusing System;\n```").ToList();

            var codeTag = tags[0].Children[0];

            Assert.AreEqual("code", codeTag.Element);
            Assert.AreEqual(0, codeTag.Attributes.Count);
            Assert.AreEqual(1, codeTag.Classes.Count);
            Assert.AreEqual("lang-CSharp", codeTag.Classes[0]);

            var fullHtml = string.Join(string.Empty, tags);
            Assert.AreEqual("<pre><code class='lang-CSharp'>using System;\n</code></pre>", fullHtml);
        }
    }
}
