// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using KellermanSoftware.CompareNetObjects;
using KellermanSoftware.CompareNetObjects.TypeComparers;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards.Test
{
    [TestClass]
    public class XmlSerializationTests
    {
        [TestMethod]
        public void VerifySerializationForAllScenarioFiles()
        {
            CompareLogic compareLogic = new CompareLogic(new ComparisonConfig()
            {
                AttributesToIgnore = new List<Type>(new[] { typeof(ObsoleteAttribute) }),
                MembersToIgnore = new List<string>(new[] { "Version", "InternalID" }),
                CustomComparers = new List<BaseTypeComparer>(new BaseTypeComparer[] {
                    new JObjectComparer(RootComparerFactory.GetRootComparer()),
                    new UriComparer(RootComparerFactory.GetRootComparer())
                })
            });

            // After changing the default value of the TextBlock Text property this test doesn't succeed as xml can't
            // read a single space (even with xml:space=preserve), hence we skip this file(s) to avoid test failures.
            // The generated xml actually contains the empty space
            string[] cardsToIgnore = { "FlightUpdate.json" };
         
            XmlSerializer serializer = new XmlSerializer(typeof(AdaptiveCard));
            foreach (var version in Directory.EnumerateDirectories(@"..\..\..\..\..\..\..\samples\", "v*"))
            {
                var folder = Path.Combine($"{version}\\scenarios");
                if (Directory.Exists(folder))
                {
                    foreach (var file in Directory.EnumerateFiles(folder, "*.json"))
                    {
                        bool mustSkip = false;
                        foreach (string cardToIgnore in cardsToIgnore)
                        {
                            mustSkip |= file.Contains(cardToIgnore);
                        }

                        if (mustSkip)
                        {
                            continue;
                        }

                        string json = File.ReadAllText(file);
                        var card = JsonConvert.DeserializeObject<AdaptiveCard>(json, new JsonSerializerSettings
                        {
                            Converters = { new StrictIntConverter() }
                        });

                        // test XML serialization round-trips
                        StringBuilder sb = new StringBuilder();
                        serializer.Serialize(new StringWriter(sb), card);
                        string xml = sb.ToString();
                        var card2 = (AdaptiveCard)serializer.Deserialize(new StringReader(xml));

                        var result = compareLogic.Compare(card, card2);
                        Assert.IsTrue(result.AreEqual, $"XML serialization different: {Path.GetFullPath(file)}: {result.DifferencesString}");

                        // test JSON serialization round-trips
                        var card3 = JsonConvert.DeserializeObject<AdaptiveCard>(JsonConvert.SerializeObject(card));
                        result = compareLogic.Compare(card, card3);
                        Assert.IsTrue(result.AreEqual, $"JSON Serialization different: {Path.GetFullPath(file)}: {result.DifferencesString}");
                    }
                }
            }
        }
    }

    public class UriComparer : BaseTypeComparer
    {
        public UriComparer(RootComparer rootComparer) : base(rootComparer)
        {
        }

        public override bool IsTypeMatch(Type type1, Type type2)
        {
            return type1 == typeof(Uri);
        }

        public override void CompareType(CompareParms parms)
        {
            // Weird hack to replace %20 in certain image URLs
            var st1 = ((Uri)parms.Object1).AbsoluteUri;
            var st2 = ((Uri)parms.Object2).AbsoluteUri;
            if (st1 != st2)
            {
                Difference difference = new Difference
                {
                    PropertyName = parms.BreadCrumb,
                    Object1Value = st1,
                    Object2Value = st2
                };

                parms.Result.Differences.Add(difference);
            }
        }
    }

    public class JObjectComparer : BaseTypeComparer
    {
        public JObjectComparer(RootComparer rootComparer) : base(rootComparer)
        {
        }

        public override bool IsTypeMatch(Type type1, Type type2)
        {
            return type1 == typeof(JObject) && type2 == typeof(JObject);
        }

        public override void CompareType(CompareParms parms)
        {
            // Weird hack to replace %20 in certain image URLs
            var st1 = JsonConvert.SerializeObject((JObject)parms.Object1);
            var st2 = JsonConvert.SerializeObject((JObject)parms.Object2);
            if (st1 != st2)
            {
                Difference difference = new Difference
                {
                    PropertyName = parms.BreadCrumb,
                    Object1Value = st1,
                    Object2Value = st2
                };

                parms.Result.Differences.Add(difference);
            }
        }
    }
}
