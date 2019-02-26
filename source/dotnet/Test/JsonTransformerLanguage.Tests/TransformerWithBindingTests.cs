using JsonTransformLanguage;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace JsonTransformerLanguage.Tests
{
    [TestClass]
    public class TransformerWithBindingTests
    {
        [TestMethod]
        public void StringInterpolation1()
        {
            TestPayload();
        }

        [TestMethod]
        public void StringLiterals1()
        {
            TestPayload();
        }

        private void TestPayload([CallerMemberName]string payloadName = null)
        {
            var parsed = JObject.Parse(File.ReadAllText(Directory.GetCurrentDirectory() + "\\TestBindingPayloads\\" + payloadName + ".json"));

            AssertTransform(parsed["inputJson"], parsed["inputData"], parsed["expected"], payloadName);
        }

        private void AssertTransform(JToken inputJson, JToken inputData, JToken expected, string testCaseName)
        {
            JToken actual = JsonTransformer.Transform(inputJson, inputData, new Dictionary<string, JToken>(), outputBindings: true);

            Assert.AreEqual(expected.ToString(), actual?.ToString());
        }
    }
}
