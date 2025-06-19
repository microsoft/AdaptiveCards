// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class SystemTextJsonExampleTests
    {
        [TestMethod]
        public void TestBasicSystemTextJsonWorkflow()
        {
            // Create a simple card
#pragma warning disable 0618
            var card = new AdaptiveCard("1.0");
#pragma warning restore 0618
            
            card.FallbackText = "This card requires a newer client";
            card.Speak = "Welcome to our service";
            
            // Add a text block
            card.Body.Add(new AdaptiveTextBlock("Hello, World!")
            {
                Size = AdaptiveTextSize.Large,
                Weight = AdaptiveTextWeight.Bolder,
                Color = AdaptiveTextColor.Accent
            });
            
            // Add an action
            card.Actions.Add(new AdaptiveSubmitAction
            {
                Title = "Submit",
                Id = "submitButton"
            });

            // Test JSON serialization with System.Text.Json
            string systemTextJson = card.ToJson();
            
            // Validate the JSON contains expected content
            Assert.IsTrue(systemTextJson.Contains("Hello, World!"));
            Assert.IsTrue(systemTextJson.Contains("Submit"));
            Assert.IsTrue(systemTextJson.Contains("1.0"));
            Assert.IsTrue(systemTextJson.Contains("AdaptiveCard"));
            
            // Test JSON deserialization with System.Text.Json
            var parseResult = AdaptiveCard.FromJson(systemTextJson);
            var deserializedCard = parseResult.Card;
            
            // Validate deserialized card
            Assert.IsNotNull(deserializedCard);
            Assert.AreEqual("1.0", deserializedCard.Version.ToString());
            Assert.AreEqual("This card requires a newer client", deserializedCard.FallbackText);
            Assert.AreEqual("Welcome to our service", deserializedCard.Speak);
            
            // Validate body
            Assert.AreEqual(1, deserializedCard.Body.Count);
            Assert.IsTrue(deserializedCard.Body[0] is AdaptiveTextBlock);
            
            var textBlock = (AdaptiveTextBlock)deserializedCard.Body[0];
            Assert.AreEqual("Hello, World!", textBlock.Text);
            Assert.AreEqual(AdaptiveTextSize.Large, textBlock.Size);
            Assert.AreEqual(AdaptiveTextWeight.Bolder, textBlock.Weight);
            Assert.AreEqual(AdaptiveTextColor.Accent, textBlock.Color);
            
            Console.WriteLine("System.Text.Json serialization/deserialization working correctly!");
            Console.WriteLine("Generated JSON:");
            Console.WriteLine(systemTextJson);
        }

        [TestMethod]
        public void TestSystemTextJsonSerialization()
        {
            // Create a card
#pragma warning disable 0618
            var card = new AdaptiveCard("1.0");
#pragma warning restore 0618
            card.FallbackText = "Compatibility test";
            card.Body.Add(new AdaptiveTextBlock("Test message"));

            // Serialize with System.Text.Json (now the default)
            string json = card.ToJson();

            // Should contain the key information
            Assert.IsTrue(json.Contains("Test message"));
            Assert.IsTrue(json.Contains("1.0"));
            Assert.IsTrue(json.Contains("Compatibility test"));

            // JSON should be valid and parseable
            var parseResult = AdaptiveCard.FromJson(json);

            Assert.IsNotNull(parseResult.Card);
        }
    }
}