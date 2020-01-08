// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using Windows.ApplicationModel.Core;
using Windows.UI.Core;
using System.Threading.Tasks;
using UWPTestLibrary;
using AdaptiveCards.Rendering.Uwp;

namespace UWPUnitTests
{
    [TestClass]
    public class RenderTests
    {
        [TestMethod]
        public async Task Media()
        {
            AdaptiveCard card = new AdaptiveCard
            {
                Version = "1.3"
            };

            AdaptiveMediaSource mediaSource = new AdaptiveMediaSource
            {
                MimeType = "audio/mp4",
                Url = "https://www.stuff.com/media.mp4"
            };

            AdaptiveMedia media = new AdaptiveMedia();
            media.Sources.Add(mediaSource);

            card.Body.Add(media);

            await RenderInDispatcher(card);
        }

        public async Task RenderInDispatcher(AdaptiveCard card)
        {
            RenderedAdaptiveCard renderedCard = null;

            // Need to move the test to the UI Thread to render the card
            var dispatcher = CoreApplication.MainView.CoreWindow.Dispatcher;
            await dispatcher.RunAsync(CoreDispatcherPriority.Normal, async () =>
            {
                var renderer = new AdaptiveCardRenderer();

                renderedCard = renderer.RenderAdaptiveCard(card);
            });

            Assert.AreEqual(0, renderedCard.Warnings.Count);
            Assert.AreEqual(0, renderedCard.Errors.Count);
        }
    }
}
