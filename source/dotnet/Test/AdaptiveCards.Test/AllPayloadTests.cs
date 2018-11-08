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

        private void TestPayloadsInDirectory(string path, string[] excludedCards)
        {
            var exceptions = new List<Exception>();
            var files = Directory.GetFiles(path, "*.json").ToList();
            Assert.IsTrue(files.Count >= 1);
            foreach (var file in files)
            {
                bool excluded = false;
                if (excludedCards != null)
                {
                    foreach (var card in excludedCards)
                    {
                        if (file.Contains(card))
                        {
                            excluded = true;
                            break;
                        }
                    }
                }

                try
                {
                    var json = File.ReadAllText(file, Encoding.UTF8);
                    AdaptiveCardParseResult parseResult;
                    try
                    {
                        parseResult = AdaptiveCard.FromJson(json);
                    }
                    catch
                    {
                        // If the card is excluded we might not parse properly
                        // skip it if there was a parse failure.
                        if(!excluded)
                        {
                            throw;
                        }
                        else
                        {
                            continue;
                        }
                    }
                    Assert.IsNotNull(parseResult.Card);
                    if (excluded)
                    {
                        // If the card was excluded but parsed, then it would have warnings
                        // If it doesn't then it shouldn't be excluded
                        Assert.AreNotEqual(0, parseResult.Warnings.Count);
                        Assert.IsNotNull(parseResult.Card.Body);
                    }
                    else
                    {
                        Assert.AreEqual(0, parseResult.Warnings.Count);
                        Assert.IsNotNull(parseResult.Card.Body);
                    }

                    // Make sure JsonConvert works also
                    var card = JsonConvert.DeserializeObject<AdaptiveCard>(json, new JsonSerializerSettings
                    {
                        Converters = { new StrictIntConverter() }
                    });
                    Assert.AreEqual(parseResult.Card.Body.Count, card.Body.Count);
                    Assert.AreEqual(parseResult.Card.Actions.Count, card.Actions.Count);
                }
                catch (Exception ex)
                {
                    exceptions.Add(new Exception($"Payload file failed: {Path.GetFileName(file)}", ex));
                }
            }

            if (exceptions.Count > 0)
            {
                throw new AggregateException(exceptions);
            }
        }

        [TestMethod]
        public void TestAllScenarios()
        {
            TestPayloadsInDirectory(Path.Combine(SamplesPath, "v1.0", "scenarios"), null);
        }

        [TestMethod]
        public void TestAllElements()
        {
            // TODO: bring this test back once I investigate the warnings
            TestPayloadsInDirectory(Path.Combine(SamplesPath, "v1.0", "elements"),
                new string[]
                {
                    // TODO: bring these tests back when bug #940 is closed
                    "Container.Style",
                    "Action.ShowCard.Style"
                });
        }

        [TestMethod]
        public void TestAllTestCards()
        {
            // List of json payloads that are expected to fail parsing
            TestPayloadsInDirectory(Path.Combine(SamplesPath, "tests"),
                new string[]
                {
                    // These cards are expected to fail
                    "AdaptiveCard.UnknownElements",
                    "AdditionalProperty",
                    "CustomParsingTestUsingProgressBar",
                    "TypeIsRequired",
                    "AdaptiveCard.MinVersion",
                    "AdaptiveCard.MissingVersion",
                    "AdaptiveCard.Version1.3",
                    "FlightItinerary_es_fail",
                    "Action.DuplicateIds"

                    // These are cards that features haven't been implemented yet
                });
        }
    }
}
