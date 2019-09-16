// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json;

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
            Assert.AreEqual(1, inputElement.Min);
            Assert.AreEqual(5, inputElement.Value);
            Assert.AreEqual(22, inputElement.Max);
            Assert.AreEqual("number", inputElement.Id);

            // Test serialization
            var resultJson = card?.ToJson();
            Assert.AreEqual(json, resultJson);
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
            Assert.AreEqual(double.NaN, inputElement.Value);

            // Test serialization
            var resultJson = card.ToJson();
            Assert.IsFalse(resultJson.Contains("\"value\""));
            Assert.AreEqual(json, resultJson);
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
            Assert.AreEqual(double.NaN, inputElement.Min);

            // Test serialization
            var resultJson = card.ToJson();
            Assert.IsFalse(resultJson.Contains("\"min\""));
            Assert.AreEqual(json, resultJson);
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
            Assert.AreEqual(double.NaN, inputElement.Max);

            // Test serialization
            var resultJson = card.ToJson();
            Assert.IsFalse(resultJson.Contains("\"max\""));
            Assert.AreEqual(json, resultJson);
        }
    }
}
