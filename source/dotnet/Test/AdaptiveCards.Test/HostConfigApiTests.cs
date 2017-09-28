using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using AdaptiveCards.Rendering.Config;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class HostConfigApiTests
    {
        [TestMethod]
        public void TestParsingHostConfig()
        {
            var result = HostConfig.FromJson(@"{
    ""fontSizes"": {
        ""small"": 25,
        ""default"": 26,
        ""medium"": 27,
        ""large"": 28,
        ""extraLarge"": 29
    }
}");

            Assert.IsNotNull(result.HostConfig);

            Assert.AreEqual(25, result.HostConfig.FontSizes.Small);
            Assert.AreEqual(26, result.HostConfig.FontSizes.Default);
#pragma warning disable 612, 618
            Assert.AreEqual(26, result.HostConfig.FontSizes.Normal);
#pragma warning restore 612, 618
            Assert.AreEqual(27, result.HostConfig.FontSizes.Medium);
            Assert.AreEqual(28, result.HostConfig.FontSizes.Large);
            Assert.AreEqual(29, result.HostConfig.FontSizes.ExtraLarge);
        }

        [TestMethod]
        public void TestParsingInvaoidHostConfig()
        {
            var result = HostConfig.FromJson("not json");

            Assert.IsNull(result.HostConfig);
        }
    }
}
