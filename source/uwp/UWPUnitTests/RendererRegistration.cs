// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCards.Rendering.Uwp;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Windows.ApplicationModel.Core;
using Windows.Data.Json;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using UWPTestLibrary;

namespace UWPUnitTests
{
    [TestClass]
    public class RendererRegistrationTests
    {
        [TestMethod]
        public async Task ActionRendererRegistraton_DefaultActionsPresent()
        {
            var dispatcher = CoreApplication.MainView.CoreWindow.Dispatcher;

            // Need to move the test to the UI Thread
            Exception dispatcherException = null;
            await dispatcher.RunAsync(CoreDispatcherPriority.Normal, async () =>
            {
                try
                {
                    AdaptiveCardRenderer renderer = new AdaptiveCardRenderer();

                    Assert.IsNotNull(renderer.ActionRenderers.Get("Action.OpenUrl"));
                    Assert.IsNotNull(renderer.ActionRenderers.Get("Action.ShowCard"));
                    Assert.IsNotNull(renderer.ActionRenderers.Get("Action.Submit"));
                    Assert.IsNotNull(renderer.ActionRenderers.Get("Action.ToggleVisibility"));
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
        }

        class TestCustomAction : IAdaptiveActionElement
        {
            public TestCustomAction()
            {
            }

            public JsonObject ToJson()
            {
                return new JsonObject();
            }
            public JsonObject AdditionalProperties { get; set; }
            public string Id { get { return "TestID"; } set { } }
            public ActionType ActionType { get { return ActionType.Custom; } }
            public string ActionTypeString { get { return "TestCustomAction"; } }
            public string IconUrl { get { return ""; } set { } }
            public string Style { get; set; }
            public string Title { get; set; }

            public IAdaptiveActionElement FallbackContent => throw new NotImplementedException();

            public FallbackType FallbackType => throw new NotImplementedException();

            IAdaptiveActionElement IAdaptiveActionElement.FallbackContent { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
            FallbackType IAdaptiveActionElement.FallbackType { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
        };

        class TestActionParser : IAdaptiveActionParser
        {
            public IAdaptiveActionElement FromJson(JsonObject inputJson, AdaptiveElementParserRegistration elementParsers, AdaptiveActionParserRegistration actionParsers, IList<AdaptiveWarning> warnings)
            {
                return new TestCustomAction() as IAdaptiveActionElement;
            }
        };

        class TestCustomActionRenderer : IAdaptiveActionRenderer
        {
            public UIElement Render(IAdaptiveActionElement action, AdaptiveRenderContext context, AdaptiveRenderArgs renderArgs)
            {
                RadioButton customActionRadioButton = new RadioButton();
                customActionRadioButton.Name = "CustomActionRadioButton";
                return customActionRadioButton;
            }
        }

        class TestSubmitActionRenderer : IAdaptiveActionRenderer
        {
            public UIElement Render(IAdaptiveActionElement action, AdaptiveRenderContext context, AdaptiveRenderArgs renderArgs)
            {
                RadioButton submitActionRadioButton = new RadioButton();
                submitActionRadioButton.Name = "SubmitActionRadioButton";
                return submitActionRadioButton;
            }
        }

        [TestMethod]
        public async Task ActionRendererRegistraton_CustomActionTest()
        {
            var dispatcher = CoreApplication.MainView.CoreWindow.Dispatcher;

            AdaptiveActionParserRegistration actionParserRegistration = new AdaptiveActionParserRegistration();
            List<AdaptiveWarning> warnings = new List<AdaptiveWarning>();

            actionParserRegistration.Set("TestCustomAction", new TestActionParser());

            String testCard =
                "{" +
                "   \"type\":\"AdaptiveCard\"," +
                "   \"version\":\"1.0\"," +
                "   \"body\":" +
                "   [" +
                "   ]," +
                "   \"actions\":" +
                "   [" +
                "       {" +
                "           \"type\":\"TestCustomAction\"" +
                "       }," +
                "       {" +
                "           \"type\":\"Action.Submit\"" +
                "       }" +
                "   ]" +
                "}";

            AdaptiveCard card = AdaptiveCard.FromJsonString(testCard, null, actionParserRegistration).AdaptiveCard;
            Assert.IsNotNull(card);


            // Need to move the test to the UI Thread to render
            Exception dispatcherException = null;
            await dispatcher.RunAsync(CoreDispatcherPriority.Normal, async () =>
            {
                try
                {
                    AdaptiveCardRenderer renderer = new AdaptiveCardRenderer();

                    renderer.ActionRenderers.Set("TestCustomAction", new TestCustomActionRenderer());
                    renderer.ActionRenderers.Set("Action.Submit", new TestSubmitActionRenderer());

                    Assert.IsNotNull(renderer.ActionRenderers.Get("TestCustomAction") as TestCustomActionRenderer);
                    Assert.IsNotNull(renderer.ActionRenderers.Get("Action.Submit") as TestSubmitActionRenderer);

                    FrameworkElement renderedCard = renderer.RenderAdaptiveCard(card).FrameworkElement;

                    bool submitFound = false;
                    bool customFound = false;
                    foreach (var radioButton in RenderTestHelpers.GetAllDescendants(renderedCard).OfType<RadioButton>())
                    {
                        customFound |= radioButton.Name == "CustomActionRadioButton";
                        submitFound |= radioButton.Name == "SubmitActionRadioButton";
                    }

                    Assert.IsTrue(customFound && submitFound);

                    renderer.ActionRenderers.Remove("TestCustomAction");
                    renderer.ActionRenderers.Remove("Action.Submit");
                    renderer.ActionRenderers.Remove("TestCustomActionThatDoesntExist");
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
        }
    }
}
