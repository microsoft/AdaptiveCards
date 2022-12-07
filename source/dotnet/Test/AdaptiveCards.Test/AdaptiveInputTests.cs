// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AdaptiveInputTests
    {
        [TestMethod]
        public void TestThatInputsRequireId()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.0"",
  ""body"": [
    {
      ""type"": ""Input.Text""
    }
  ]
}";

            var ex = Assert.ThrowsException<AdaptiveSerializationException>(() =>
            {
                AdaptiveCard.FromJson(json);
            });

            StringAssert.Contains(ex.Message, "'id'");
        }

        [TestMethod]
        public void TestPassWordInputStyle()
        {
            var expectedJSON = Utilities.BuildExpectedCardJSON("textInput", new SerializableDictionary<string, object>() { ["style"] = "Password" });
            var testCard = AdaptiveCard.FromJson(expectedJSON);
            Assert.IsTrue(testCard.Warnings.Count == 0);
            AdaptiveTextInput textInput = Utilities.GetAdaptiveElementWithId(testCard.Card, "textInput") as AdaptiveTextInput;
            Assert.IsNotNull(textInput);
            Assert.AreEqual(AdaptiveTextInputStyle.Password, textInput.Style);
        }
    }
}
