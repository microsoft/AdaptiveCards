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
    }
}
