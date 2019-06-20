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
            await dispatcher.RunAsync(CoreDispatcherPriority.Normal, async () =>
            {
                AdaptiveCardRenderer renderer = new AdaptiveCardRenderer();

                Assert.IsNotNull(renderer.ActionRenderers.Get("Action.OpenUrl"));
                Assert.IsNotNull(renderer.ActionRenderers.Get("Action.ShowCard"));
                Assert.IsNotNull(renderer.ActionRenderers.Get("Action.Submit"));
                Assert.IsNotNull(renderer.ActionRenderers.Get("Action.ToggleVisibility"));
            });

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

            // Need to move the test to the UI Thread
            await dispatcher.RunAsync(CoreDispatcherPriority.Normal, async () =>
            {
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
            });
        }
    }
}
