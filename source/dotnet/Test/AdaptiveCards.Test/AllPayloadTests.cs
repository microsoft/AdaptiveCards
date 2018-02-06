using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using Microsoft.DotNet.PlatformAbstractions;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AllPayloadTests
    {
        public static string SamplesPath => Path.Combine(ApplicationEnvironment.ApplicationBasePath, "..", "..", "..", "..", "..", "..", "..", "samples");

        private void TestPayloadsInDirectory(string path)
        {
            var exceptions = new List<Exception>();
            var files = Directory.GetFiles(path, "*.json").ToList();
            Assert.IsTrue(files.Count > 1);
            foreach (var file in files)
            {
                // TODO: bring these tests back when bug #940 is closed
                if (file.Contains("Container.Style") || file.Contains("ShowCard.Style"))
                    continue;

                try
                {
                    var json = File.ReadAllText(file, Encoding.UTF8);
                    var parseResult = AdaptiveCard.FromJson(json);
                    Assert.IsNotNull(parseResult.Card);
                    Assert.AreEqual(0, parseResult.Warnings.Count);

                    // Make sure JsonConvert works also
                    var card = JsonConvert.DeserializeObject<AdaptiveCard>(json);
                    Assert.AreEqual(parseResult.Card.Body.Count, card.Body.Count);
                    Assert.AreEqual(parseResult.Card.Actions.Count, card.Actions.Count);
                }
                catch (Exception ex)
                {
                    exceptions.Add(new Exception($"Payload file failed: {Path.GetFileName(file)}", ex));
                }

            }

            if (exceptions.Count > 0)
                throw new AggregateException(exceptions);
        }

        [TestMethod]
        public void TestAllScenarios()
        {
            TestPayloadsInDirectory(Path.Combine(SamplesPath, "v1.0", "scenarios"));
        }

        [TestMethod]
        public void TestAllElements()
        {
            // TODO: bring this test back once I investigate the warnings
            TestPayloadsInDirectory(Path.Combine(SamplesPath, "v1.0", "elements"));
        }
    }
}
