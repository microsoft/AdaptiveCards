using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AdaptiveCardSeparatorSpacingTests
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

            TextBlock tb = card.Body[0] as TextBlock;

            Assert.AreEqual(Spacing.Large, tb.Spacing);
            Assert.AreEqual(true, tb.Separator);

            // Assert legacy prop
#pragma warning disable 612, 618
            Assert.AreEqual(SeparationStyle.Strong, tb.Separation);
#pragma warning restore 612, 618

            string json = card.ToJson();

            Assert.IsFalse(json.Contains(@"""separator"": true"));
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

            TextBlock tb = card.Body[0] as TextBlock;

            Assert.AreEqual(Spacing.Default, tb.Spacing);
            Assert.AreEqual(false, tb.Separator);

            string json = card.ToJson();

            Assert.IsFalse(json.Contains("spacing"));
            Assert.IsFalse(json.Contains("separator"));
            Assert.IsFalse(json.Contains("separation"));
        }

        [TestMethod]
        public void TestLegacySeparation()
        {
            AdaptiveCard card = AdaptiveCard.FromJson(@"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Adaptive Card design session"",
      ""separation"": ""none""
    },
    {
      ""type"": ""TextBlock"",
      ""text"": ""Adaptive Card design session""
    },
    {
      ""type"": ""TextBlock"",
      ""text"": ""Adaptive Card design session"",
      ""separation"": ""default""
    },
    {
      ""type"": ""TextBlock"",
      ""text"": ""Adaptive Card design session"",
      ""separation"": ""strong""
    }
  ]
}").Card;

#pragma warning disable 612, 618
            Assert.AreEqual(SeparationStyle.None, card.Body[0].Separation);
            Assert.AreEqual(SeparationStyle.Default, card.Body[1].Separation);
            Assert.AreEqual(SeparationStyle.Default, card.Body[2].Separation);
            Assert.AreEqual(SeparationStyle.Strong, card.Body[3].Separation);
#pragma warning restore 612, 618

            Assert.AreEqual(Spacing.None, card.Body[0].Spacing);
            Assert.AreEqual(Spacing.Default, card.Body[1].Spacing);
            Assert.AreEqual(Spacing.Default, card.Body[2].Spacing);
            Assert.AreEqual(Spacing.Large, card.Body[3].Spacing);

            Assert.AreEqual(false, card.Body[0].Separator);
            Assert.AreEqual(false, card.Body[1].Separator);
            Assert.AreEqual(false, card.Body[2].Separator);
            Assert.AreEqual(true, card.Body[3].Separator);

            // Make sure assigning via object model works correctly too
#pragma warning disable 612, 618
            card.Body[0].Separation = SeparationStyle.Strong;
            card.Body[1].Separation = SeparationStyle.Default;
            card.Body[2].Separation = SeparationStyle.None;

            Assert.AreEqual(SeparationStyle.Strong, card.Body[0].Separation);
            Assert.AreEqual(SeparationStyle.Default, card.Body[1].Separation);
            Assert.AreEqual(SeparationStyle.None, card.Body[2].Separation);
#pragma warning restore 612, 618

            Assert.AreEqual(Spacing.Large, card.Body[0].Spacing);
            Assert.AreEqual(Spacing.Default, card.Body[1].Spacing);
            Assert.AreEqual(Spacing.None, card.Body[2].Spacing);

            Assert.AreEqual(true, card.Body[0].Separator);
            Assert.AreEqual(false, card.Body[1].Separator);
            Assert.AreEqual(false, card.Body[2].Separator);
        }

        [TestMethod]
        public void TestAllSpacingValues()
        {
            TestSpacing(Spacing.Small, "small");
            TestSpacing(Spacing.Default, "default");
            TestSpacing(Spacing.Medium, "medium");
            TestSpacing(Spacing.Large, "large");
            TestSpacing(Spacing.ExtraLarge, "extraLarge");
            TestSpacing(Spacing.Padding, "padding");
        }

        private void TestSpacing(Spacing expected, string spacingString)
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

            TextBlock tb = card.Body[0] as TextBlock;
            Assert.AreEqual(expected, tb.Spacing);

            string json = card.ToJson();
            string str = $@"""spacing"":""{spacingString}""";

            if (expected == Spacing.Default)
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
