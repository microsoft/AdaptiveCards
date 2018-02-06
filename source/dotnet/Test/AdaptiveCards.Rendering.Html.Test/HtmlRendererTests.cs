using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace AdaptiveCards.Rendering.Html.Test
{
    [TestClass]
    public class HtmlRendererTests
    {
        [TestMethod]
        public void TextBlockRender_ParagraphElementStylesAdded()
        {
            var renderContext = new AdaptiveRenderContext(
                new AdaptiveHostConfig(),
                new AdaptiveElementRenderers<HtmlTag, AdaptiveRenderContext>());

            var textBlock = new AdaptiveTextBlock
            {
                Text = "first line\n\nsecond line",
            };

            var generatedHtml = TestHtmlRenderer.CallTextBlockRender(textBlock, renderContext).ToString();

            // From String

            // Generated HTML should have two <p> tags, with appropriate styles set.
            Assert.AreEqual(
                "<div class=\'ac-textblock\' style=\'box-sizing: border-box;text-align: left;color: rgba(0, 0, 0, 1.00);line-height: 18.62px;font-size: 14px;font-weight: 400;white-space: nowrap;\'><p style=\'margin-top: 0px;margin-bottom: 0px;width: 100%;text-overflow: ellipsis;overflow: hidden;\'>first line</p><p style=\'margin-top: 0px;margin-bottom: 0px;width: 100%;text-overflow: ellipsis;overflow: hidden;\'>second line</p></div>",
                generatedHtml);
        }



        private class TestHtmlRenderer : AdaptiveCardRenderer
        {
            public TestHtmlRenderer(AdaptiveHostConfig config)
                : base(config)
            {
            }

            public static HtmlTag CallTextBlockRender(AdaptiveTextBlock element, AdaptiveRenderContext context)
            {
                return TextBlockRender(element, context);
            }
        }
    }
}
