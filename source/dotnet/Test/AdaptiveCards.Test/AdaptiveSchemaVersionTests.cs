// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AdaptiveSchemaVersionTests
    {
        [TestMethod]
        public void OperatorTests()
        {
            var v10 = new AdaptiveSchemaVersion(1, 0);
            var v11 = new AdaptiveSchemaVersion(1, 1);

            Assert.IsFalse(v10 == v11);
            Assert.IsFalse(v10.Equals(v11));
            Assert.IsTrue(v11 > v10);
            Assert.IsTrue(v10 < v11);
            Assert.IsTrue(v11 >= v10);
        }


        [TestMethod]
        public void TestVersionParsing()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""1.1""
}";

            var result = AdaptiveCard.FromJson(json);

            Assert.AreEqual(new AdaptiveSchemaVersion(1, 1), result.Card.Version);
        }

        [TestMethod]
        public void Test_InvalidVersionStringFailsParsing()
        {
            var json = @"{
  ""type"": ""AdaptiveCard"",
  ""version"": ""invalid"",
  ""body"": [
    {
      ""type"": ""TextBlock"",
      ""text"": ""Hello""
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
