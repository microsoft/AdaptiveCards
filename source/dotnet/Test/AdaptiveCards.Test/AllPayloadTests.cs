// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class AllPayloadTests
    {
        public static string SamplesPath => Path.Combine(System.AppContext.BaseDirectory, "..", "..", "..", "..", "..", "..", "..", "samples");

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
                        if (!excluded)
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
                        Assert.AreNotEqual(0, parseResult.Warnings.Count, "If an excluded card parsed correctly, it should have warnings");
                        Assert.IsNotNull(parseResult.Card.Body, "A parsed card should have a body");
                    }
                    else
                    {
                        Assert.IsNotNull(parseResult.Card.Body, "A passing card should have a body");
                    }

                    // Make sure JsonConvert works also
                    var card = JsonConvert.DeserializeObject<AdaptiveCard>(json, new JsonSerializerSettings
                    {
                        Converters = { new StrictIntConverter() },
                        Error = delegate(object sender, Newtonsoft.Json.Serialization.ErrorEventArgs args)
                        {
                            if (args.ErrorContext.Error.GetType() == typeof(JsonSerializationException))
                            {
                                args.ErrorContext.Handled = true;
                            }
                        }
                    });
                    Assert.AreEqual(parseResult.Card.Body.Count, card.Body.Count, "A converted card should have the same number of body elements as the parsed card");
                    Assert.AreEqual(parseResult.Card.Actions.Count, card.Actions.Count, "A converted card should have the same number of actions as the parsed card");
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
            TestPayloadsInDirectory(Path.Combine(SamplesPath, "v1.1", "scenarios"), null);
        }

        [TestMethod]
        public void TestAllElements()
        {
            TestPayloadsInDirectory(Path.Combine(SamplesPath, "v1.0", "elements"), null);
            TestPayloadsInDirectory(Path.Combine(SamplesPath, "v1.1", "elements"), null);
            TestPayloadsInDirectory(Path.Combine(SamplesPath, "v1.2", "elements"), null);
        }

        [TestMethod]
        public void TestAllTestCards()
        {

            TestPayloadsInDirectory(Path.Combine(SamplesPath, "v1.0", "tests"),
                new string[]
                {   
                    // These cards are expected to fail
                    "TypeIsRequired",
                    "AdaptiveCard.MissingVersion",
                });

            TestPayloadsInDirectory(Path.Combine(SamplesPath, "v1.1", "tests"), null);
            TestPayloadsInDirectory(Path.Combine(SamplesPath, "v1.2", "tests"),
                new string[]
                {
                    // These cards are expected to fail
                    "Action.DuplicateIds",
                    "Action.NestedDuplicateIds",
                });

            TestPayloadsInDirectory(Path.Combine(SamplesPath, "v1.3", "tests"), null); 
        }
    }
}
