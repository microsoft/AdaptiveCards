using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards.Templating.Test
{
    [TestClass]
    public class TestTransform
    {
        [TestMethod]
        public void TestBasic()
        {
            AdaptiveTransformer transformer = new AdaptiveTransformer();

            string jsonTemplate = @"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
     ""$data"": {
            ""employee"": {
                ""name"": ""Matt"",
                ""manager"": { ""name"": ""Thomas"" },
                ""peers"": [{
                    ""name"": ""Andrew"" 
                }, { 
                    ""name"": ""Lei""
                }, { 
                    ""name"": ""Mary Anne""
                }, { 
                    ""name"": ""Adam""
                }]
            }
        },
    ""body"": [
        {
            ""type"": ""TextBlock"",
            ""text"": ""{person.firstName}""
        }
    ]
}";

            string jsonData = @"{
    ""person"": {
        ""firstName"": ""Andrew"",
        ""lastName"": ""Leader""
    }
}";

            string cardJson = transformer.Transform(jsonTemplate, jsonData);

            AssertJsonEqual(@"{
    ""type"": ""AdaptiveCard"",
    ""version"": ""1.0"",
    ""body"": [
        {
            ""type"": ""TextBlock"",
            ""text"": ""Andrew""
        }
    ]
}", cardJson);
        }

        private static void AssertJsonEqual(string jsonExpected, string jsonActual)
        {
            var expected = JObject.Parse(jsonExpected);
            var actual = JObject.Parse(jsonActual);

            Assert.IsTrue(JToken.DeepEquals(expected, actual), "JSON wasn't the same.\n\nExpected: " + expected.ToString() + "\n\nActual: " + actual.ToString());
        }
    }
}
