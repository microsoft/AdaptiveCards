using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using Microsoft.DotNet.PlatformAbstractions;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AllPayloadTests
    {
        public static string SamplesPath => Path.Combine(ApplicationEnvironment.ApplicationBasePath, "..", "..", "..", "..", "..", "..", "..", "samples");

        private void TestPayloadsInDirectory(string path)
        {
            var files = Directory.GetFiles(path, "*.json").ToList();
            Assert.IsTrue(files.Count > 1);
            foreach (var file in files)
            {
                try
                {
                    var parseResult = AdaptiveCard.FromJson(File.ReadAllText(file, Encoding.UTF8));
                    Assert.IsNotNull(parseResult.Card);
                    Assert.AreEqual(0, parseResult.Warnings.Count);
                }
                catch (Exception ex)
                {
                    throw new Exception($"Payload file failed: {file}", ex);
                }

            }
        }

        [TestMethod]
        public void TestAllScenarios()
        {
            TestPayloadsInDirectory(Path.Combine(SamplesPath, "v1.0", "scenarios"));
        }

        [TestMethod]
        public void TestAllElements()
        {
            TestPayloadsInDirectory(Path.Combine(SamplesPath, "v1.0", "elements"));
        }
    }
}
