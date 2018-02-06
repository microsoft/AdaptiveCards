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

            // Assert legacy prop
#pragma warning disable 612, 618
            Assert.AreEqual(AdaptiveSeparationStyle.Strong, tb.Separation);
#pragma warning restore 612, 618

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
            Assert.AreEqual(AdaptiveSeparationStyle.None, card.Body[0].Separation);
            Assert.AreEqual(AdaptiveSeparationStyle.Default, card.Body[1].Separation);
            Assert.AreEqual(AdaptiveSeparationStyle.Default, card.Body[2].Separation);
            Assert.AreEqual(AdaptiveSeparationStyle.Strong, card.Body[3].Separation);
#pragma warning restore 612, 618

            Assert.AreEqual(AdaptiveSpacing.None, card.Body[0].Spacing);
            Assert.AreEqual(AdaptiveSpacing.Default, card.Body[1].Spacing);
            Assert.AreEqual(AdaptiveSpacing.Default, card.Body[2].Spacing);
            Assert.AreEqual(AdaptiveSpacing.Large, card.Body[3].Spacing);

            Assert.AreEqual(false, card.Body[0].Separator);
            Assert.AreEqual(false, card.Body[1].Separator);
            Assert.AreEqual(false, card.Body[2].Separator);
            Assert.AreEqual(true, card.Body[3].Separator);

            // Make sure assigning via object model works correctly too
#pragma warning disable 612, 618
            card.Body[0].Separation = AdaptiveSeparationStyle.Strong;
            card.Body[1].Separation = AdaptiveSeparationStyle.Default;
            card.Body[2].Separation = AdaptiveSeparationStyle.None;

            Assert.AreEqual(AdaptiveSeparationStyle.Strong, card.Body[0].Separation);
            Assert.AreEqual(AdaptiveSeparationStyle.Default, card.Body[1].Separation);
            Assert.AreEqual(AdaptiveSeparationStyle.None, card.Body[2].Separation);
#pragma warning restore 612, 618

            Assert.AreEqual(AdaptiveSpacing.Large, card.Body[0].Spacing);
            Assert.AreEqual(AdaptiveSpacing.Default, card.Body[1].Spacing);
            Assert.AreEqual(AdaptiveSpacing.None, card.Body[2].Spacing);

            Assert.AreEqual(true, card.Body[0].Separator);
            Assert.AreEqual(false, card.Body[1].Separator);
            Assert.AreEqual(false, card.Body[2].Separator);
        }

        [TestMethod]
        public void TestSerializingLegacySeparation()
        {
            var inputJson = @"{
 ""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
 ""type"": ""AdaptiveCard"",
 ""version"": ""1.0"",
 ""body"": [
    {
        ""type"": ""TextBlock"",
        ""text"": ""Line 1"",
        ""separation"": ""default""
    },
    {
        ""type"": ""TextBlock"",
        ""text"": ""separation:default"",
        ""separation"": ""default""
    },
    {
        ""type"": ""TextBlock"",
        ""text"": ""separation:none"",
        ""separation"": ""none""
    },
    {
        ""type"": ""TextBlock"",
        ""text"": ""separation:strong"",
        ""separation"": ""strong""
    }
 ]
}";

            var expectedJson = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Line 1""
    },
    {
      ""type"": ""TextBlock"",
      ""text"": ""separation:default""
    },
    {
      ""type"": ""TextBlock"",
      ""text"": ""separation:none"",
      ""spacing"": ""none"",
      ""separation"": ""none""
    },
    {
      ""type"": ""TextBlock"",
      ""text"": ""separation:strong"",
      ""spacing"": ""large"",
      ""separator"": true,
      ""separation"": ""strong""
    }
  ]
}";

            var card = AdaptiveCard.FromJson(inputJson).Card;
            Assert.AreEqual(expectedJson, card.ToJson());
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
