// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using System.Text.RegularExpressions;

namespace AdaptiveCards.Rendering.Html.Test
{
    [TestClass]
    public class HtmlRendererTests
    {

        [TestMethod]
        public void TextBlockRender_ItalicAndStrikethrough()
        {
            AdaptiveCard card = new AdaptiveCard("1.2")
            {
                Body = new System.Collections.Generic.List<AdaptiveElement>()
                {
                    new AdaptiveTextBlock("Some italic struck-through text")
                    {
                        Italic = true,
                        Strikethrough = true
                    }
                }
            };


            var renderer = new AdaptiveCardRenderer();
            var result = renderer.RenderCard(card);
            var generatedHtml = result.Html.ToString();

            Assert.AreEqual("<div class='ac-adaptivecard' style='width: 100%;background-color: rgba(255, 255, 255, 1.00);padding: 15px;box-sizing: border-box;justify-content: flex-start;'><div class='ac-textblock' style='box-sizing: border-box;text-align: left;color: rgba(0, 0, 0, 1.00);line-height: 18.62px;font-size: 14px;font-weight: 400;font-style: italic;text-decoration: line-through;white-space: nowrap;'><p style='margin-top: 0px;margin-bottom: 0px;width: 100%;text-overflow: ellipsis;overflow: hidden;'>Some italic struck-through text</p></div></div>",
                generatedHtml);
        }

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
                "<div class='ac-textblock' style='box-sizing: border-box;text-align: left;color: rgba(0, 0, 0, 1.00);line-height: 18.62px;font-size: 14px;font-weight: 400;white-space: nowrap;'><p style='margin-top: 0px;margin-bottom: 0px;width: 100%;text-overflow: ellipsis;overflow: hidden;'>first line</p><p style='margin-top: 0px;margin-bottom: 0px;width: 100%;text-overflow: ellipsis;overflow: hidden;'>second line</p></div>",
                generatedHtml);
        }

        [TestMethod]
        public void RichTextBlockRender_MultipleInlines()
        {
            var card = new AdaptiveCard("1.2")
            {
                Body = new System.Collections.Generic.List<AdaptiveElement>()
                {
                    new AdaptiveRichTextBlock()
                    {
                        Inlines = {
                            new AdaptiveTextRun
                            {
                                Text = "Inline 1"
                            },
                            new AdaptiveTextRun
                            {
                                Text = "Inline 2"
                            },
                            new AdaptiveTextRun
                            {
                                Text = "Inline 3"
                            },
                            new AdaptiveTextRun
                            {
                                Text = "Inline 4",
                                Italic = true,
                                Strikethrough = true,
                                Highlight = true
                            }
                        }
                    }
                }
            };

            var renderer = new AdaptiveCardRenderer();
            var result = renderer.RenderCard(card);
            var generatedHtml = result.Html.ToString();

            Assert.AreEqual(
                "<div class='ac-adaptivecard' style='width: 100%;background-color: rgba(255, 255, 255, 1.00);padding: 15px;box-sizing: border-box;justify-content: flex-start;'><div class='ac-richtextblock' style='box-sizing: border-box;text-align: left;word-wrap: break-word;'><p style='margin-top: 0px;margin-bottom: 0px;width: 100%;'><span class='ac-textrun' style='color: rgba(0, 0, 0, 1.00);line-height: 18.62px;font-size: 14px;font-weight: 400;'>Inline 1</span><span class='ac-textrun' style='color: rgba(0, 0, 0, 1.00);line-height: 18.62px;font-size: 14px;font-weight: 400;'>Inline 2</span><span class='ac-textrun' style='color: rgba(0, 0, 0, 1.00);line-height: 18.62px;font-size: 14px;font-weight: 400;'>Inline 3</span><span class='ac-textrun' style='color: rgba(0, 0, 0, 1.00);line-height: 18.62px;font-size: 14px;font-weight: 400;font-style: italic;text-decoration: line-through;background-color: rgba(255, 255, 0, 1.00);'>Inline 4</span></p></div></div>",
                generatedHtml);
        }

        [TestMethod]
        public void TextBlocks_Markdown()
        {
            var card = new AdaptiveCard("1.2")
            {
                Body = new System.Collections.Generic.List<AdaptiveElement>()
                {
                    new AdaptiveRichTextBlock()
                    {
                        Inlines = {
                            new AdaptiveTextRun
                            {
                                Text = "The RichTextBlock should not support **markdown**"
                            }
                        }
                    },
                    new AdaptiveTextBlock()
                    {
                        Text = "The TextBlock should support **markdown**"
                    }
                }
            };

            var renderer = new AdaptiveCardRenderer();
            var result = renderer.RenderCard(card);
            var generatedHtml = result.Html.ToString();

            var randomGeneratedIds = FindAllRandomGeneratedIds(generatedHtml);

            Assert.AreEqual(
                "<div class='ac-adaptivecard' style='width: 100%;background-color: rgba(255, 255, 255, 1.00);padding: 15px;box-sizing: border-box;justify-content: flex-start;'><div class='ac-richtextblock' style='box-sizing: border-box;text-align: left;word-wrap: break-word;'><p style='margin-top: 0px;margin-bottom: 0px;width: 100%;'><span class='ac-textrun' style='color: rgba(0, 0, 0, 1.00);line-height: 18.62px;font-size: 14px;font-weight: 400;'>The RichTextBlock should not support **markdown**</span></p></div><div class='ac-separator' id='" + randomGeneratedIds[0] + "' style='height: 8px;'></div><div class='ac-textblock' data-ac-separatorId='" + randomGeneratedIds[0] + "' style='box-sizing: border-box;text-align: left;color: rgba(0, 0, 0, 1.00);line-height: 18.62px;font-size: 14px;font-weight: 400;white-space: nowrap;'><p style='margin-top: 0px;margin-bottom: 0px;width: 100%;text-overflow: ellipsis;overflow: hidden;'>The TextBlock should support <strong>markdown</strong></p></div></div>",
                generatedHtml);
        }

        [TestMethod]
        public void RenderFallbackItem()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.2"",
  ""body"": [
    {
      ""type"": ""Graph"",
      ""text"": ""First textblock"",
      ""fallback"": {
        ""type"": ""TextBlock"",
        ""text"": ""Fallback textblock""
      }
    }
  ]
}";

            var card = AdaptiveCard.FromJson(json).Card;

            var renderer = new AdaptiveCardRenderer();
            var result = renderer.RenderCard(card);
            var generatedHtml = result.Html.ToString();

            Assert.AreEqual("<div class='ac-adaptivecard' style='width: 100%;background-color: rgba(255, 255, 255, 1.00);padding: 15px;box-sizing: border-box;justify-content: flex-start;'><div class='ac-textblock' style='box-sizing: border-box;text-align: left;color: rgba(0, 0, 0, 1.00);line-height: 18.62px;font-size: 14px;font-weight: 400;white-space: nowrap;'><p style='margin-top: 0px;margin-bottom: 0px;width: 100%;text-overflow: ellipsis;overflow: hidden;'>Fallback textblock</p></div></div>", generatedHtml);
        }

        [TestMethod]
        public void ContainerStyleForegroundColors()
        {
            var hostConfig = new AdaptiveHostConfig();
            hostConfig.ContainerStyles.Emphasis.ForegroundColors = new ForegroundColorsConfig()
            {
                Default = new FontColorConfig("#FFcc3300")
            };

            var card = new AdaptiveCard("1.2")
            {
                Body = new System.Collections.Generic.List<AdaptiveElement>()
                {
                    new AdaptiveContainer()
                    {
                        Style = AdaptiveContainerStyle.Emphasis,
                        Items = new System.Collections.Generic.List<AdaptiveElement>()
                        {
                            new AdaptiveTextBlock()
                            {
                                Text = "container 1 -- emphasis style text"
                            },
                            new AdaptiveContainer()
                            {
                                Style = AdaptiveContainerStyle.Accent,
                                Items = new System.Collections.Generic.List<AdaptiveElement>()
                                {
                                    new AdaptiveTextBlock()
                                    {
                                        Text = "container 1.1 -- accent style text"
                                    }
                                }
                            },
                            new AdaptiveTextBlock()
                            {
                                Text = "container 1 -- emphasis style text"
                            }
                        }
                    },
                    new AdaptiveTextBlock()
                    {
                        Text = "default style text"
                    }
                }
            };

            var renderer = new AdaptiveCardRenderer(hostConfig);
            var result = renderer.RenderCard(card);
            var generatedHtml = result.Html.ToString();

            var randomGeneratedIds = FindAllRandomGeneratedIds(generatedHtml);

            Assert.AreEqual(
                "<div class='ac-adaptivecard' style='width: 100%;background-color: rgba(255, 255, 255, 1.00);padding: 15px;box-sizing: border-box;justify-content: flex-start;'><div class='ac-container' style='padding-right: 15px;padding-left: 15px;padding-top: 15px;padding-bottom: 15px;background-color: rgba(0, 0, 0, 0.03);justify-content: flex-start;'><div class='ac-textblock' style='box-sizing: border-box;text-align: left;color: rgba(204, 51, 0, 1.00);line-height: 18.62px;font-size: 14px;font-weight: 400;white-space: nowrap;'><p style='margin-top: 0px;margin-bottom: 0px;width: 100%;text-overflow: ellipsis;overflow: hidden;'>container 1 -- emphasis style text</p></div><div class='ac-separator' id='" + randomGeneratedIds[0] + "' style='height: 8px;'></div><div class='ac-container' data-ac-separatorId='" + randomGeneratedIds[0] + "' style='padding-right: 15px;padding-left: 15px;padding-top: 15px;padding-bottom: 15px;background-color: #dce5f7;justify-content: flex-start;'><div class='ac-textblock' style='box-sizing: border-box;text-align: left;color: rgba(0, 0, 0, 1.00);line-height: 18.62px;font-size: 14px;font-weight: 400;white-space: nowrap;'><p style='margin-top: 0px;margin-bottom: 0px;width: 100%;text-overflow: ellipsis;overflow: hidden;'>container 1.1 -- accent style text</p></div></div><div class='ac-separator' id='" + randomGeneratedIds[1] + "' style='height: 8px;'></div><div class='ac-textblock' data-ac-separatorId='" + randomGeneratedIds[1] + "' style='box-sizing: border-box;text-align: left;color: rgba(204, 51, 0, 1.00);line-height: 18.62px;font-size: 14px;font-weight: 400;white-space: nowrap;'><p style='margin-top: 0px;margin-bottom: 0px;width: 100%;text-overflow: ellipsis;overflow: hidden;'>container 1 -- emphasis style text</p></div></div><div class='ac-separator' id='" + randomGeneratedIds[2] + "' style='height: 8px;'></div><div class='ac-textblock' data-ac-separatorId='" + randomGeneratedIds[2] + "' style='box-sizing: border-box;text-align: left;color: rgba(0, 0, 0, 1.00);line-height: 18.62px;font-size: 14px;font-weight: 400;white-space: nowrap;'><p style='margin-top: 0px;margin-bottom: 0px;width: 100%;text-overflow: ellipsis;overflow: hidden;'>default style text</p></div></div>",
                generatedHtml);
        }

        public List<string> FindAllRandomGeneratedIds(string html)
        {
            List<string> randomGeneratedIds = new List<string>();

            string pattern = "id='ac-[0-9a-f]{8}'";

            Regex regex = new Regex(pattern);
            MatchCollection matches = regex.Matches(html);

            foreach (Match match in matches)
            {
                // The actual id is located in the range
                randomGeneratedIds.Add(match.Value.Substring(4, 11));
            }

            return randomGeneratedIds;
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

            public static HtmlTag CallChoiceSetInputRender(AdaptiveChoiceSetInput element, AdaptiveRenderContext context)
            {
                return ChoiceSetRender(element, context);
            }

            public static HtmlTag CallContainerRender(AdaptiveContainer element, AdaptiveRenderContext context)
            {
                return ContainerRender(element, context);
            }
        }

        [TestMethod]
        public void ChoiceSetInput()
        {
            var renderContext = new AdaptiveRenderContext(
                new AdaptiveHostConfig(),
                new AdaptiveElementRenderers<HtmlTag, AdaptiveRenderContext>());

            var dropdownList = new AdaptiveChoiceSetInput()
            {
                Id = "1",
                Value = "1,3",
                Style = AdaptiveChoiceInputStyle.Compact,
                Choices =
                {
                    new AdaptiveChoice()
                    {
                        Title = "Value 1",
                        Value = "1"
                    },
                    new AdaptiveChoice()
                    {
                        Title = "Value 2",
                        Value = "2"
                    },
                    new AdaptiveChoice()
                    {
                        Title = "Value 3",
                        Value = "3"
                    }
                }
            };

            var dropdownGeneratedHtml = TestHtmlRenderer.CallChoiceSetInputRender(dropdownList, renderContext).ToString();

            // Generated HTML should have an additional disabled and hidden option which is selected.
            Assert.AreEqual(
                "<select class='ac-input ac-multichoiceInput' name='1' style='width: 100%;'><option disabled='' hidden='' selected=''/><option value='1'>Value 1</option><option value='2'>Value 2</option><option value='3'>Value 3</option></select>",
                dropdownGeneratedHtml);
        }



        [TestMethod]
        public void BleedProperty()
        {
            var renderContext = new AdaptiveRenderContext(
                new AdaptiveHostConfig(),
                new AdaptiveElementRenderers<HtmlTag, AdaptiveRenderContext>());

            renderContext.ElementRenderers.Set<AdaptiveContainer>(TestHtmlRenderer.CallContainerRender);
            renderContext.RenderArgs.ParentStyle = AdaptiveContainerStyle.Default;

            var containerWithWorkingBleed = new AdaptiveContainer
            {
                Style = AdaptiveContainerStyle.Default,
                Items = new System.Collections.Generic.List<AdaptiveElement>
                {
                    new AdaptiveContainer()
                    {
                        Style = AdaptiveContainerStyle.Emphasis,
                        Bleed = true,
                        Items = new System.Collections.Generic.List<AdaptiveElement>()
                    }
                }
            };

            renderContext.RenderArgs.ParentStyle = AdaptiveContainerStyle.Default;

            var containerWithoutWorkingBleed = new AdaptiveContainer
            {
                Style = AdaptiveContainerStyle.Default,
                Items = new System.Collections.Generic.List<AdaptiveElement>
                {
                    new AdaptiveContainer()
                    {
                        Style = AdaptiveContainerStyle.Default,
                        Bleed = true,
                        Items = new System.Collections.Generic.List<AdaptiveElement>()
                    }
                }
            };

            var workingBleedHtml = TestHtmlRenderer.CallContainerRender(containerWithWorkingBleed, renderContext).ToString();
            var notWorkingBleedHtml = TestHtmlRenderer.CallContainerRender(containerWithoutWorkingBleed, renderContext).ToString();

            // Generated HTML should have an additional disabled and hidden option which is selected.
            Assert.AreEqual(
                "<div class='ac-container' style='background-color: rgba(255, 255, 255, 1.00);justify-content: flex-start;'><div class='ac-container' style='padding-right: 15px;padding-left: 15px;padding-top: 15px;padding-bottom: 15px;margin-right: -15px;margin-left: -15px;margin-top: -15px;margin-bottom: -15px;background-color: rgba(0, 0, 0, 0.03);justify-content: flex-start;'></div></div>",
                workingBleedHtml);

            Assert.AreEqual(
                "<div class='ac-container' style='background-color: rgba(255, 255, 255, 1.00);justify-content: flex-start;'><div class='ac-container' style='background-color: rgba(255, 255, 255, 1.00);justify-content: flex-start;'></div></div>",
                notWorkingBleedHtml);
        }
    }
}
