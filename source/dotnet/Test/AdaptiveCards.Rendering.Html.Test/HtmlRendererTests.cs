using AdaptiveCards.Rendering;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using AdaptiveCards.Rendering.Html;

namespace AdaptiveCards.Html.Test
{
    [TestClass]
    public class HtmlRendererTests
    {
        [TestMethod]
        public void TextBlockRender_ParagraphElementStylesAdded()
        {
            var renderContext = new RenderContext(
                new HostConfig(),
                new ElementRenderers<HtmlTag, RenderContext>());

            var textBlock = new TextBlock
            {
                Text = "first line\n\nsecond line",
            };

            var generatedHtml = TestHtmlRenderer.CallTextBlockRender(textBlock, renderContext).ToString();

            // Generated HTML should have two <p> tags, with appropriate styles set.
            Assert.AreEqual(
                "<div class='ac-textblock' style='text-align: left;box-sizing: border-box;color: rgba(0, 0, 0, 1.00);line-height: 14.40px;font-size: 12px;font-weight: 400;font-family: Calibri;white-space: nowrap;'><p style='margin-top: 0px;margin-bottom: 0px;width: 100%;text-overflow: ellipsis;overflow: hidden;'>first line</p><p style='margin-top: 0px;margin-bottom: 0px;width: 100%;text-overflow: ellipsis;overflow: hidden;'>second line</p></div>",
                generatedHtml);
        }

        private class TestHtmlRenderer : AdaptiveCardRenderer
        {
            public TestHtmlRenderer(HostConfig config)
                : base(config)
            {
            }

            public static HtmlTag CallTextBlockRender(TextBlock element, RenderContext context)
            {
                return TextBlockRender(element, context);
            }
        }
    }
}
