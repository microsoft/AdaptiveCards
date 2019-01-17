using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.CompilerServices;
using System.Text;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class BindingPayloadTests
    {
        [TestMethod]
        public void SportsScore()
        {
            TestPayload();
        }

        [TestMethod]
        public void People()
        {
            TestPayload();
        }

        private void TestPayload([CallerMemberName]string payloadName = null)
        {
            string cardJson = File.ReadAllText(Directory.GetCurrentDirectory() + "\\BindingTestPayloads\\" + payloadName + ".json");

            string expectedJson = File.ReadAllText(Directory.GetCurrentDirectory() + "\\BindingTestPayloads\\" + payloadName + "-expected.json");

            AssertTransform(cardJson, expectedJson);
        }

        private void AssertTransform(string cardJson, string expectedJson)
        {
            var actualResult = AdaptiveCard.ResolveFromJson(cardJson, null);
            var expectedResult = AdaptiveCard.FromJson(expectedJson);

            Assert.AreEqual(expectedResult.Card.ToJson(), actualResult.Card.ToJson());
        }
    }
}
