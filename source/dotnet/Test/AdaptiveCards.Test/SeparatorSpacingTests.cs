// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class SeparatorSpacingTests
    {
        [TestMethod]
        public void TestSpacingAndSeparator()
        {
            AdaptiveCard card = AdaptiveCard.FromJson(@"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Adaptive Card design session"",
      ""spacing"": ""large"",
      ""separator"": true
    }
  ]
}").Card;

            AdaptiveTextBlock tb = card.Body[0] as AdaptiveTextBlock;

            Assert.AreEqual(AdaptiveSpacing.Large, tb.Spacing);
            Assert.AreEqual(true, tb.Separator);

            string json = card.ToJson();

            Assert.IsTrue(json.Contains(@"""separator"": true"));
        }

        [TestMethod]
        public void TestSpacingAndSeparatorDefaults()
        {
            AdaptiveCard card = AdaptiveCard.FromJson(@"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Adaptive Card design session""
    }
  ]
}").Card;

            AdaptiveTextBlock tb = card.Body[0] as AdaptiveTextBlock;

            Assert.AreEqual(AdaptiveSpacing.Default, tb.Spacing);
            Assert.AreEqual(false, tb.Separator);

            string json = card.ToJson();

            Assert.IsFalse(json.Contains("spacing"));
            Assert.IsFalse(json.Contains("separator"));
        }

        [TestMethod]
        public void TestAllSpacingValues()
        {
            TestSpacing(AdaptiveSpacing.Small, "small");
            TestSpacing(AdaptiveSpacing.Default, "default");
            TestSpacing(AdaptiveSpacing.Medium, "medium");
            TestSpacing(AdaptiveSpacing.Large, "large");
            TestSpacing(AdaptiveSpacing.ExtraLarge, "extraLarge");
            TestSpacing(AdaptiveSpacing.Padding, "padding");
        }

        private void TestSpacing(AdaptiveSpacing expected, string spacingString)
        {
            AdaptiveCard card = AdaptiveCard.FromJson(@"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Adaptive Card design session"",
      ""spacing"": """ + spacingString + @"""
    }
  ]
}").Card;

            AdaptiveTextBlock tb = card.Body[0] as AdaptiveTextBlock;
            Assert.AreEqual(expected, tb.Spacing);

            string json = card.ToJson();
            string str = $@"""spacing"": ""{spacingString}""";

            if (expected == AdaptiveSpacing.Default)
            {
                Assert.IsFalse(json.Contains(str));
            }
            else
            {
                Assert.IsTrue(json.Contains(str));
            }
        }
    }
}
