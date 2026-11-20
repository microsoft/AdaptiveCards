// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Text.Json;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AdaptiveNumberInputTests
    {
        [TestMethod]
        public void TestThatSerializationWorks()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""Input.Number"",
      ""id"": ""number"",
      ""placeholder"": ""Pick a number"",
      ""value"": 5.0,
      ""min"": 1.0,
      ""max"": 22.0
    }
  ]
}";

            // Test deserialization
            var cardResult = AdaptiveCard.FromJson(json);
            var card = cardResult.Card;

            var inputElement = card?.Body?.FirstOrDefault() as AdaptiveNumberInput;
            Assert.IsNotNull(inputElement);
            Assert.AreEqual("Pick a number", inputElement.Placeholder);
            Assert.AreEqual(1.0, inputElement.Min);
            Assert.AreEqual(5.0, inputElement.Value);
            Assert.AreEqual(22.0, inputElement.Max);
            Assert.AreEqual("number", inputElement.Id);

            // Test serialization roundtrip
            var resultJson = card?.ToJson();
            var reparsed = AdaptiveCard.FromJson(resultJson).Card;
            var reparsedInput = reparsed?.Body?.FirstOrDefault() as AdaptiveNumberInput;
            Assert.IsNotNull(reparsedInput);
            Assert.AreEqual("Pick a number", reparsedInput.Placeholder);
            Assert.AreEqual(1.0, reparsedInput.Min);
            Assert.AreEqual(5.0, reparsedInput.Value);
            Assert.AreEqual(22.0, reparsedInput.Max);
            Assert.AreEqual("number", reparsedInput.Id);
        }

        [TestMethod]
        public void TestThatNaNValueIsDroppedOnSerialization()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""Input.Number"",
      ""id"": ""number"",
      ""placeholder"": ""Pick a number"",
      ""min"": 1.0,
      ""max"": 22.0
    }
  ]
}";

            // Test deserialization
            var cardResult = AdaptiveCard.FromJson(json);
            var card = cardResult.Card;
            var inputElement = card.Body.FirstOrDefault() as AdaptiveNumberInput;
            Assert.IsNotNull(inputElement);
            Assert.IsNull(inputElement.Value);

            // Test serialization
            var resultJson = card.ToJson();
            Assert.IsFalse(resultJson.Contains("\"value\""));
            var reparsed = AdaptiveCard.FromJson(resultJson).Card;
            var reparsedInput = reparsed.Body.FirstOrDefault() as AdaptiveNumberInput;
            Assert.IsNotNull(reparsedInput);
            Assert.IsNull(reparsedInput.Value);
            Assert.AreEqual(1.0, reparsedInput.Min);
            Assert.AreEqual(22.0, reparsedInput.Max);
        }

        [TestMethod]
        public void TestThatNaNMinIsDroppedOnSerialization()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""Input.Number"",
      ""id"": ""number"",
      ""placeholder"": ""Pick a number"",
      ""value"": 5.0,
      ""max"": 22.0
    }
  ]
}";

            // Test deserialization
            var cardResult = AdaptiveCard.FromJson(json);
            var card = cardResult.Card;
            var inputElement = card.Body.FirstOrDefault() as AdaptiveNumberInput;
            Assert.IsNotNull(inputElement);
            Assert.IsNull(inputElement.Min);

            // Test serialization
            var resultJson = card.ToJson();
            Assert.IsFalse(resultJson.Contains("\"min\""));
            var reparsed = AdaptiveCard.FromJson(resultJson).Card;
            var reparsedInput = reparsed.Body.FirstOrDefault() as AdaptiveNumberInput;
            Assert.IsNotNull(reparsedInput);
            Assert.AreEqual(5.0, reparsedInput.Value);
            Assert.IsNull(reparsedInput.Min);
            Assert.AreEqual(22.0, reparsedInput.Max);
        }

        [TestMethod]
        public void TestThatNaNMaxIsDroppedOnSerialization()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""Input.Number"",
      ""id"": ""number"",
      ""placeholder"": ""Pick a number"",
      ""value"": 5.0,
      ""min"": 1.0
    }
  ]
}";

            // Test deserialization
            var cardResult = AdaptiveCard.FromJson(json);
            var card = cardResult.Card;
            var inputElement = card.Body.FirstOrDefault() as AdaptiveNumberInput;
            Assert.IsNotNull(inputElement);
            Assert.IsNull(inputElement.Max);

            // Test serialization
            var resultJson = card.ToJson();
            Assert.IsFalse(resultJson.Contains("\"max\""));
            var reparsed = AdaptiveCard.FromJson(resultJson).Card;
            var reparsedInput = reparsed.Body.FirstOrDefault() as AdaptiveNumberInput;
            Assert.IsNotNull(reparsedInput);
            Assert.AreEqual(5.0, reparsedInput.Value);
            Assert.AreEqual(1.0, reparsedInput.Min);
            Assert.IsNull(reparsedInput.Max);
        }
    }
}
