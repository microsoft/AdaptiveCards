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
    }
}
