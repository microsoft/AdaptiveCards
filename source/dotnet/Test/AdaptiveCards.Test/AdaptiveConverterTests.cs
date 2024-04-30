// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json;
using System;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AdaptiveConverterTests
    {
        [TestMethod]
        public void TestIsoDateTimeConverter()
        {
            var date = DateTime.Parse("05/25/1967 12:35pm").ToUniversalTime();
            var datestr = date.ToString("yyyy-MM-ddTHH:mm:ssZ");

            AdaptiveRefresh refresh = new AdaptiveRefresh()
            {
                Expires = date
            };
            var json = JsonConvert.SerializeObject(refresh);
            Assert.IsTrue(json.Contains(datestr));
            var refresh2 = JsonConvert.DeserializeObject<AdaptiveRefresh>(json);
            Assert.AreEqual(date, refresh2.Expires);
        }
    }
}
