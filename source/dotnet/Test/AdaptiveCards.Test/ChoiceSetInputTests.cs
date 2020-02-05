// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class ChoiceSetInputTests
    {

        [TestMethod]
        public void TestChoiceSetExpanded()
        {
            var card = new AdaptiveCard("1.0")
            {
                Body = new List<AdaptiveElement>()
                {
                    new AdaptiveTextBlock()
                    {
                        Text = "Hello",
                        Weight = AdaptiveTextWeight.Bolder
                    },
                    new AdaptiveChoiceSetInput()
                    {
                        Id = "choiceTest",
                        Style = AdaptiveChoiceInputStyle.Expanded
                    }
                }
            };


            var expected = @"""style"": ""expanded""";

            StringAssert.Contains(card.ToJson(), expected);
        }

        [TestMethod]
        public void TestChoiceSetWrap()
        {
            var card = new AdaptiveCard("1.2")
            {
                Body = new List<AdaptiveElement>()
                {
                    new AdaptiveTextBlock()
                    {
                        Text = "Hello",
                        Weight = AdaptiveTextWeight.Bolder
                    },
                    new AdaptiveChoiceSetInput()
                    {
                        Id = "choiceTest",
                        Wrap = true
                    }
                }
            };

            var expected = @"""wrap"": true";

            StringAssert.Contains(card.ToJson(), expected);
        }
    }
}
