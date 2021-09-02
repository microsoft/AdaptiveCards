// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCards.ObjectModel.Uwp;
using AdaptiveCards.Rendering.Uwp;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Threading.Tasks;
using Windows.ApplicationModel.Core;
using Windows.UI.Core;
using Windows.UI.Xaml;

namespace UWPUnitTests
{
    // This test class ensures that the individual element renderers can be successfully constructed and
    // used by calling apps. Confirmation of the UI generated and interactions with it are in the
    // UWPUITests test libraray.
    [TestClass]
    public class ElementRenderTests
    {
        class TestInputToggleRenderer : IAdaptiveElementRenderer
        {
            public UIElement Render(IAdaptiveCardElement element, AdaptiveRenderContext context, AdaptiveRenderArgs renderArgs)
            {
                // Confirm we can construct a toggle renderer and use it to render the toggle element
                AdaptiveToggleInputRenderer toggleRenderer = new AdaptiveToggleInputRenderer();
                UIElement renderedElement = toggleRenderer.Render(element, context, renderArgs);
                Assert.IsNotNull(renderedElement);
                return renderedElement;
            }
        }

        [TestMethod]
        public async Task InputRendererTest()
        {
            AdaptiveCard card = new AdaptiveCard
            {
                Version = "1.5"
            };

            AdaptiveToggleInput toggleInput = new AdaptiveToggleInput
            {
                Value = "onValue",
                ValueOff = "offValue",
                ValueOn = "onValue",
                Wrap = true,
                Title = "This is the title of my toggle input",
            };

            card.Body.Add(toggleInput);

            var dispatcher = CoreApplication.MainView.CoreWindow.Dispatcher;
            Exception dispatcherException = null;
            RenderedAdaptiveCard renderedCard = null;
            await dispatcher.RunAsync(CoreDispatcherPriority.Normal, async () =>
            {
                try
                {
                    // Register the custom toggle renderer
                    AdaptiveCardRenderer renderer = new AdaptiveCardRenderer();
                    renderer.ElementRenderers.Set("Input.Toggle", new TestInputToggleRenderer());

                    renderedCard = renderer.RenderAdaptiveCard(card);

                }
                catch (Exception e)
                {
                    // If we throw an exception from inside the dispatcher the test infrastructure loses its
                    // connection with the tests. Hold onto this and throw it from the main test thread so
                    // it is reported properly as a test failure.
                    dispatcherException = e;
                }
            });

            if (dispatcherException != null)
            {
                // Rethrow any exceptions that may have happened within the dispatcher
                throw dispatcherException;
            }

            Assert.AreEqual(0, renderedCard.Warnings.Count);
            Assert.AreEqual(0, renderedCard.Errors.Count);
        }
    }
}
