// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace AdaptiveCards.Rendering.Html.Test
{
    [TestClass]
    public class AdaptiveActionTests
    {
        [TestMethod]
        public void TestActionCssClassesAreNamedProperly()
        {
            Assert.AreEqual("ac-action-showCard", AdaptiveCardRenderer.GetActionCssClass(new AdaptiveShowCardAction()));
            Assert.AreEqual("ac-action-submit", AdaptiveCardRenderer.GetActionCssClass(new AdaptiveSubmitAction()));
            Assert.AreEqual("ac-action-openUrl", AdaptiveCardRenderer.GetActionCssClass(new AdaptiveOpenUrlAction()));
        }

        // a sanity test that Visit method does terminates for all Adaptive elements
        [TestMethod]
        public void AdaptiveVisitorTest()
        {
            AdaptiveCard adaptiveCard = new AdaptiveCard("1.3");

            AdaptiveActionSet actionSet = new AdaptiveActionSet();
            actionSet.Actions.Add(new AdaptiveToggleVisibilityAction());
            actionSet.Actions.Add(new AdaptiveSubmitAction());
            actionSet.Actions.Add(new AdaptiveOpenUrlAction());
            actionSet.Actions.Add(new AdaptiveShowCardAction());
            adaptiveCard.Body.Add(actionSet);

            adaptiveCard.Body.Add(new AdaptiveTextBlock());
            adaptiveCard.Body.Add(new AdaptiveRichTextBlock());
            adaptiveCard.Body.Add(new AdaptiveFactSet());

            adaptiveCard.Body.Add(new AdaptiveImage());
            adaptiveCard.Body.Add(new AdaptiveImageSet());
            adaptiveCard.Body.Add(new AdaptiveMedia());

            adaptiveCard.Body.Add(new AdaptiveChoiceSetInput());
            adaptiveCard.Body.Add(new AdaptiveTextInput());
            adaptiveCard.Body.Add(new AdaptiveNumberInput());
            adaptiveCard.Body.Add(new AdaptiveDateInput());
            adaptiveCard.Body.Add(new AdaptiveTimeInput());

            adaptiveCard.Body.Add(new AdaptiveColumn());
            adaptiveCard.Body.Add(new AdaptiveColumnSet());
            adaptiveCard.Body.Add(new AdaptiveContainer());

            adaptiveCard.Body.Add(new AdaptiveUnknownElement());

            AdaptiveVisitor visitor = new AdaptiveVisitor();
            visitor.Visit(adaptiveCard);
            // The below check checks that the visit method doesn't hang 
            Assert.IsTrue(true);
        }

    }
}
