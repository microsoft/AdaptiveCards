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

            // Test System.Text.Json serialization
            string systemTextJson = card.ToJsonSystemText();
            
            // Validate the JSON contains expected content
            Assert.IsTrue(systemTextJson.Contains("Hello, World!"));
            Assert.IsTrue(systemTextJson.Contains("Submit"));
            Assert.IsTrue(systemTextJson.Contains("1.0"));
            Assert.IsTrue(systemTextJson.Contains("AdaptiveCard"));
            
            // Test System.Text.Json deserialization
            var parseResult = AdaptiveCard.FromJsonSystemText(systemTextJson);
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
        public void TestSystemTextJsonCompatibilityWithNewtonsoftJson()
        {
            // Create a card
#pragma warning disable 0618
            var card = new AdaptiveCard("1.0");
#pragma warning restore 0618
            card.FallbackText = "Compatibility test";
            card.Body.Add(new AdaptiveTextBlock("Test message"));

            // Serialize with both libraries
            string newtonsoftJson = card.ToJson();
            string systemTextJson = card.ToJsonSystemText();

            // Both should contain the same key information
            Assert.IsTrue(newtonsoftJson.Contains("Test message"));
            Assert.IsTrue(systemTextJson.Contains("Test message"));
            Assert.IsTrue(newtonsoftJson.Contains("1.0"));
            Assert.IsTrue(systemTextJson.Contains("1.0"));
            Assert.IsTrue(newtonsoftJson.Contains("Compatibility test"));
            Assert.IsTrue(systemTextJson.Contains("Compatibility test"));

            // Both should be valid JSON (can be parsed by the other serializer)
            var newtonsoftParseResult = AdaptiveCard.FromJson(systemTextJson);
            var systemTextParseResult = AdaptiveCard.FromJsonSystemText(newtonsoftJson);

            Assert.IsNotNull(newtonsoftParseResult.Card);
            Assert.IsNotNull(systemTextParseResult.Card);
        }
    }
}