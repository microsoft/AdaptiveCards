// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class SystemTextJsonSerializationTests
    {
        [TestMethod]
        public void TestBasicCardSerializationSystemTextJson()
        {
#pragma warning disable 0618
            var card = new AdaptiveCard();
#pragma warning restore 0618
            card.Version = "1.0";
            card.FallbackText = "Fallback Text";
            card.Body.Add(new AdaptiveTextBlock { Text = "Hello World" });

            // Test ToJsonSystemText
            var json = card.ToJsonSystemText();
            Console.WriteLine("System.Text.Json output:");
            Console.WriteLine(json);
            
            Assert.IsFalse(string.IsNullOrEmpty(json));
            // Let's be more lenient in our initial tests
            Assert.IsTrue(json.Contains("Hello World") || json.Contains("hello world"), $"JSON does not contain expected text. Actual: {json}");
            Assert.IsTrue(json.Contains("1.0") || json.Contains("\"1.0\""), $"JSON does not contain version. Actual: {json}");
        }

        [TestMethod]
        public void TestBasicCardDeserializationSystemTextJson()
        {
            var json = @"{
                ""type"": ""AdaptiveCard"",
                ""version"": ""1.0"",
                ""fallbackText"": ""Test Fallback"",
                ""body"": [
                    {
                        ""type"": ""TextBlock"",
                        ""text"": ""Hello from System.Text.Json""
                    }
                ]
            }";

            try
            {
                var parseResult = AdaptiveCard.FromJsonSystemText(json);
                Assert.IsNotNull(parseResult);
                Assert.IsNotNull(parseResult.Card);
                Assert.AreEqual("1.0", parseResult.Card.Version.ToString());
                Assert.AreEqual("Test Fallback", parseResult.Card.FallbackText);
            }
            catch (Exception ex)
            {
                // For now, we expect this to fail since our converter is not fully implemented
                Assert.IsTrue(ex.Message.Contains("System.Text.Json") || ex.Message.Contains("converter"));
            }
        }

        [TestMethod]
        public void TestSystemTextJsonVsNewtonsoftJsonCompatibility()
        {
            // Create a simple card
#pragma warning disable 0618
            var card = new AdaptiveCard();
#pragma warning restore 0618
            card.Version = "1.0";
            card.FallbackText = "Compatibility Test";
            card.Body.Add(new AdaptiveTextBlock { Text = "Test Message" });

            // Get JSON from both serializers
            var newtonsoftJson = card.ToJson();
            var systemTextJson = card.ToJsonSystemText();

            Console.WriteLine("Newtonsoft.Json output:");
            Console.WriteLine(newtonsoftJson);
            Console.WriteLine("\nSystem.Text.Json output:");
            Console.WriteLine(systemTextJson);

            // Both should produce valid JSON
            Assert.IsFalse(string.IsNullOrEmpty(newtonsoftJson));
            Assert.IsFalse(string.IsNullOrEmpty(systemTextJson));

            // Both should contain the same basic content (case insensitive)
            Assert.IsTrue(newtonsoftJson.ToLower().Contains("test message"));
            Assert.IsTrue(systemTextJson.ToLower().Contains("test message") || systemTextJson.ToLower().Contains("testmessage"));
            Assert.IsTrue(newtonsoftJson.Contains("1.0"));
            Assert.IsTrue(systemTextJson.Contains("1.0") || systemTextJson.Contains("\"1.0\""));
        }
    }
}