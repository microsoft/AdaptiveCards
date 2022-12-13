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

        [TestMethod]
        public void TestChoiceSetFilteredStyle()
        {
            var expectedJSON = Utilities.BuildExpectedCardJSON("choiceSetInput", new SerializableDictionary<string, object>() { ["style"] = "filtered" });
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

            const string expectedJson = @"{
              ""type"": ""AdaptiveCard"",
              ""version"": ""1.5"",
              ""body"": [
                {
                  ""type"": ""Input.ChoiceSet"",
                  ""id"": ""id0"",
                  ""style"": ""filtered"",
                  ""isMultiSelect"": false,
                  ""choices"": []
                }
              ]
            }";

            var actualJson = Utilities.RemoveWhiteSpacesFromJSON(card.ToJson());

            Assert.AreEqual(Utilities.RemoveWhiteSpacesFromJSON(expectedJson), actualJson);

            Assert.AreEqual(Utilities.RemoveWhiteSpacesFromJSON(expectedJson), Utilities.RemoveWhiteSpacesFromJSON(AdaptiveCard.FromJson(actualJson).Card.ToJson()));
        }
    }
}
