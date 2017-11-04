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
        public void TestThatAllInputsRequireId()
        {
            var json = @"{
	""$schema"": ""http://adaptivecards.io/schemas/adaptive-card.json"",
	""type"": ""AdaptiveCard"",
	""version"": ""1.0"",
	""body"": [
		{
			""type"": ""TextBlock"",
			""text"": ""Publish Adaptives Card schema"",
			""weight"": ""bolder"",
			""size"": ""medium""
		},
		{
			""type"": ""Input.Text""
		}
	],
	""actions"": [
		{
			""type"": ""Action.OpenUrl"",
			""title"": ""View"",
			""url"": ""http://adaptivecards.io""
		}
	]
}";

            Assert.ThrowsException<AdaptiveSerializationException>(() =>
            {
                AdaptiveCard.FromJson(json);
            });
        }
    }
}
