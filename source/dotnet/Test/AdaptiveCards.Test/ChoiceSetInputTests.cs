// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;
using System.Text.Json;
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

            var json = card.ToJson();
            // Verify the expanded style roundtrips
            var reparsed = AdaptiveCard.FromJson(json).Card;
            var choiceSet = reparsed.Body[1] as AdaptiveChoiceSetInput;
            Assert.IsNotNull(choiceSet);
            Assert.AreEqual(AdaptiveChoiceInputStyle.Expanded, choiceSet.Style);
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

        [TestMethod]
        public void TestChoiceSetFilteredStyle()
        {
            var expectedJSON = Utilities.BuildExpectedCardJSON("choiceSetInput", new Dictionary<string, JsonElement>() { ["style"] = JsonSerializer.SerializeToElement("filtered") });
            var testCard = AdaptiveCard.FromJson(expectedJSON);
            Assert.IsTrue(testCard.Warnings.Count == 0);
            AdaptiveChoiceSetInput choiceSetInput = Utilities.GetAdaptiveElementWithId(testCard.Card, "choiceSetInput") as AdaptiveChoiceSetInput;
            Assert.IsNotNull(choiceSetInput);
            Assert.AreEqual(AdaptiveChoiceInputStyle.Filtered, choiceSetInput.Style);
        }

        [TestMethod]
        public void TestChoiceSetFilteredStyleDeserialization()
        {
            var sampleJSON = Utilities.GetJSONCardFromFile("Input.ChoiceSet.Filtered.json", "v1.5", "Elements");
            var card = AdaptiveCard.FromJson(sampleJSON);
            Assert.IsTrue(card.Warnings.Count == 0);
            AdaptiveChoiceSetInput choiceSetInput = Utilities.GetAdaptiveElementWithId(card.Card, "chosenAnimal") as AdaptiveChoiceSetInput;
            Assert.IsNotNull(choiceSetInput);
            Assert.AreEqual(choiceSetInput.Style, AdaptiveChoiceInputStyle.Filtered);
        }

        [TestMethod]
        public void TestChoiceSetFilteredStyleRoundTripTest()
        {
            var card = new AdaptiveCard(AdaptiveCard.KnownSchemaVersion);
            card.Body.Add(new AdaptiveChoiceSetInput()
            {
                Id = "id0",
                Style = AdaptiveChoiceInputStyle.Filtered,
            });

            var json = card.ToJson();

            // Verify roundtrip preserves filtered style
            var reparsed = AdaptiveCard.FromJson(json).Card;
            Assert.AreEqual(1, reparsed.Body.Count);
            var choiceSet = reparsed.Body[0] as AdaptiveChoiceSetInput;
            Assert.IsNotNull(choiceSet);
            Assert.AreEqual("id0", choiceSet.Id);
            Assert.AreEqual(AdaptiveChoiceInputStyle.Filtered, choiceSet.Style);

            // Verify double roundtrip
            var json2 = reparsed.ToJson();
            var reparsed2 = AdaptiveCard.FromJson(json2).Card;
            var choiceSet2 = reparsed2.Body[0] as AdaptiveChoiceSetInput;
            Assert.IsNotNull(choiceSet2);
            Assert.AreEqual(AdaptiveChoiceInputStyle.Filtered, choiceSet2.Style);
        }
    }
}
