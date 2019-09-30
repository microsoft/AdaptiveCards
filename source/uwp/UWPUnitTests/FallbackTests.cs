// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCards.Rendering.Uwp;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Threading.Tasks;
using Windows.ApplicationModel.Core;
using Windows.UI.Core;

namespace UWPUnitTests
{
    [TestClass]
    public class FallbackTests
    {
        [TestMethod]
        public async Task ColumnFallbackAsync()
        {
            string cardStr =
                "{" +
                "\"type\": \"AdaptiveCard\"," +
                "\"version\": \"1.0\"," +
                "\"body\": [" +
                "{" +
                "    \"type\": \"ColumnSet\"," +
                "    \"columns\": [" +
                "    {" +
                "        \"type\": \"Column\"," +
                "        \"items\": [" +
                "        {" +
                "            \"type\": \"Graph\"" +
                "        }]," +
                "        \"fallback\": {" +
                "            \"type\": \"Column\"," +
                "            \"items\": [" +
                "            {" +
                "                \"type\": \"TextBlock\"," +
                "                \"text\": \"Fallback\"" +
                "            }]" +
                "        }" +
                "    }]" +
                "}]}";

            var dispatcher = CoreApplication.MainView.CoreWindow.Dispatcher;

            Exception testException = null;

            // Need to move the test to the UI Thread
            await dispatcher.RunAsync(CoreDispatcherPriority.Normal, async () =>
            {
                try
                {
                    AdaptiveCardRenderer renderer = new AdaptiveCardRenderer();
                    RenderedAdaptiveCard renderedCard = renderer.RenderAdaptiveCardFromJsonString(cardStr);

                    Assert.AreEqual(1, renderedCard.Warnings.Count);
                    Assert.AreEqual("Performing fallback for element of type \"Column\" (fallback element type \"Column\")", renderedCard.Warnings[0].Message);
                }
                catch (Exception thrown)
                {
                    testException = thrown;
                }
            });

            if (testException != null)
            {
                throw testException;
            }
        }

        [TestMethod]
        public async Task RequiresAdaptiveCardsTest()
        {
            AdaptiveCard card = new AdaptiveCard();
            AdaptiveTextBlock textBlock1 = new AdaptiveTextBlock
            {
                Text = "Text Block 1 requires adaptive cards 5 and has fallback content."
            };

            AdaptiveTextBlock fallbackTextBlock = new AdaptiveTextBlock
            {
                Text = "Text Block 1 falls back to this."
            };

            textBlock1.FallbackContent = fallbackTextBlock;
            textBlock1.Requirements.Add(new AdaptiveRequirement("adaptiveCards", "5.0"));

            Assert.AreEqual(FallbackType.Content, textBlock1.FallbackType);

            card.Body.Add(textBlock1);

            AdaptiveTextBlock textBlock2 = new AdaptiveTextBlock
            {
                Text = "Text Block 2 requires adaptive cards 5 and is dropped."
            };

            textBlock2.FallbackType = FallbackType.Drop;
            textBlock2.Requirements.Add(new AdaptiveRequirement("adaptiveCards", "5.0"));

            Assert.AreEqual(FallbackType.Drop, textBlock2.FallbackType);

            card.Body.Add(textBlock2);

            AdaptiveTextBlock textBlock3 = new AdaptiveTextBlock
            {
                Text = "Text Block 3 requires adaptive cards 5 and has no specified fallback."
            };

            textBlock3.Requirements.Add(new AdaptiveRequirement("adaptiveCards", "5.0"));

            Assert.AreEqual(FallbackType.None, textBlock3.FallbackType);

            card.Body.Add(textBlock3);

            AdaptiveTextBlock textBlock4 = new AdaptiveTextBlock
            {
                Text = "Text Block 4 requires adaptive cards 1."
            };

            textBlock4.Requirements.Add(new AdaptiveRequirement("adaptiveCards", "1.0"));

            Assert.AreEqual(FallbackType.None, textBlock4.FallbackType);

            card.Body.Add(textBlock4);

            AdaptiveTextBlock textBlock5 = new AdaptiveTextBlock
            {
                Text = "Text Block 5 requires any version of adaptive cards."
            };

            textBlock5.Requirements.Add(new AdaptiveRequirement("adaptiveCards", "*"));

            Assert.AreEqual(FallbackType.None, textBlock5.FallbackType);

            card.Body.Add(textBlock5);

            var dispatcher = CoreApplication.MainView.CoreWindow.Dispatcher;

            Exception testException = null;

            // Need to move the test to the UI Thread
            await dispatcher.RunAsync(CoreDispatcherPriority.Normal, async () =>
            {
                try
                {
                    AdaptiveCardRenderer renderer = new AdaptiveCardRenderer();
                    RenderedAdaptiveCard renderedCard = renderer.RenderAdaptiveCard(card);

                    Assert.AreEqual(3, renderedCard.Warnings.Count);
                    Assert.AreEqual("Performing fallback for element of type \"TextBlock\" (fallback element type \"TextBlock\")", renderedCard.Warnings[0].Message);
                    Assert.AreEqual("Dropping element of type \"TextBlock\" for fallback", renderedCard.Warnings[1].Message);
                    Assert.AreEqual("No Renderer found for type: TextBlock", renderedCard.Warnings[2].Message); //Issue #3418
                }
                catch (Exception thrown)
                {
                    testException = thrown;
                }
            });

            if (testException != null)
            {
                throw testException;
            }
        }

        [TestMethod]
        public async Task RequiresCustomFeatureTest()
        {
            AdaptiveCard card = new AdaptiveCard();
            AdaptiveTextBlock textBlock1 = new AdaptiveTextBlock
            {
                Text = "Text Block 1 requires testFeature 5.0 and has fallback content."
            };

            AdaptiveTextBlock fallbackTextBlock = new AdaptiveTextBlock
            {
                Text = "Text Block 1 falls back to this."
            };

            textBlock1.FallbackContent = fallbackTextBlock;
            textBlock1.Requirements.Add(new AdaptiveRequirement("testFeature", "5.0"));

            Assert.AreEqual(FallbackType.Content, textBlock1.FallbackType);

            card.Body.Add(textBlock1);

            AdaptiveTextBlock textBlock2 = new AdaptiveTextBlock
            {
                Text = "Text Block 2 requires testFeature 5.0 and is dropped."
            };

            textBlock2.FallbackType = FallbackType.Drop;
            textBlock2.Requirements.Add(new AdaptiveRequirement("testFeature", "5.0"));

            Assert.AreEqual(FallbackType.Drop, textBlock2.FallbackType);

            card.Body.Add(textBlock2);

            AdaptiveTextBlock textBlock3 = new AdaptiveTextBlock
            {
                Text = "Text Block 3 requires testFeature 5 and has no specified fallback."
            };

            textBlock3.Requirements.Add(new AdaptiveRequirement("testFeature", "5.0"));

            Assert.AreEqual(FallbackType.None, textBlock3.FallbackType);

            card.Body.Add(textBlock3);

            AdaptiveTextBlock textBlock4 = new AdaptiveTextBlock
            {
                Text = "Text Block 4 requires testFeature 1."
            };

            textBlock4.Requirements.Add(new AdaptiveRequirement("adaptiveCards", "1.0"));

            Assert.AreEqual(FallbackType.None, textBlock4.FallbackType);

            card.Body.Add(textBlock4);

            AdaptiveTextBlock textBlock5 = new AdaptiveTextBlock
            {
                Text = "Text Block 5 requires any version of testFeature."
            };

            textBlock5.Requirements.Add(new AdaptiveRequirement("adaptiveCards", "*"));

            Assert.AreEqual(FallbackType.None, textBlock5.FallbackType);

            card.Body.Add(textBlock5);

            AdaptiveTextBlock textBlock6 = new AdaptiveTextBlock
            {
                Text = "Text Block 6 requires bogusFeature."
            };

            textBlock6.Requirements.Add(new AdaptiveRequirement("bogusFeature", "*"));

            Assert.AreEqual(FallbackType.None, textBlock6.FallbackType);

            card.Body.Add(textBlock6);

            AdaptiveTextBlock textBlock7 = new AdaptiveTextBlock
            {
                Text = "Text Block 7 tests case insensitive features."
            };

            textBlock7.Requirements.Add(new AdaptiveRequirement("cAsEiNsEnSiTiVeFEAture", "1.0"));

            Assert.AreEqual(FallbackType.None, textBlock7.FallbackType);

            card.Body.Add(textBlock7);

            var dispatcher = CoreApplication.MainView.CoreWindow.Dispatcher;

            Exception testException = null;

            // Need to move the test to the UI Thread
            await dispatcher.RunAsync(CoreDispatcherPriority.Normal, async () =>
            {
                try
                {
                    AdaptiveCardRenderer renderer = new AdaptiveCardRenderer();
                    renderer.FeatureRegistration.Set("testFeature", "1.0");
                    renderer.FeatureRegistration.Set("caseInsensitiveFeature", "1.0");

                    RenderedAdaptiveCard renderedCard = renderer.RenderAdaptiveCard(card);

                    Assert.AreEqual(4, renderedCard.Warnings.Count);
                    Assert.AreEqual("Performing fallback for element of type \"TextBlock\" (fallback element type \"TextBlock\")", renderedCard.Warnings[0].Message);
                    Assert.AreEqual("Dropping element of type \"TextBlock\" for fallback", renderedCard.Warnings[1].Message);
                    Assert.AreEqual("No Renderer found for type: TextBlock", renderedCard.Warnings[2].Message); //Issue #3418
                    Assert.AreEqual("No Renderer found for type: TextBlock", renderedCard.Warnings[3].Message); //Issue #3418
                }
                catch (Exception thrown)
                {
                    testException = thrown;
                }
            });

            if (testException != null)
            {
                throw testException;
            }
        }
    }
}
