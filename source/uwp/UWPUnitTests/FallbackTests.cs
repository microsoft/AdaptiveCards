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
    }
}
