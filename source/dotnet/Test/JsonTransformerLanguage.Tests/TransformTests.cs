using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.CompilerServices;
using JsonTransformLanguage;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json.Linq;

namespace JsonTransformerLanguage.Tests
{
    [TestClass]
    public class TransformTests
    {
        [TestMethod]
        public void ArrayOfObjects1()
        {
            TestPayload();
        }

        [TestMethod]
        public void ArrayOfObjects2()
        {
            TestPayload();
        }

        [TestMethod]
        public void ArrayOfStrings1()
        {
            TestPayload();
        }

        [TestMethod]
        public void ArrayOfStrings2()
        {
            TestPayload();
        }

        [TestMethod]
        public void String1()
        {
            TestPayload();
        }

        [TestMethod]
        public void Repeating1()
        {
            TestPayload();
        }

        [TestMethod]
        public void Scoping1()
        {
            TestPayload();
        }

        [TestMethod]
        public void StringInterpolation1()
        {
            TestPayload();
        }

        [TestMethod]
        public void StringInterpolationWithNotFound1()
        {
            TestPayload();
        }

        [TestMethod]
        public void PreservingDataTypes1()
        {
            TestPayload();
        }

        [TestMethod]
        public void NotFoundProperties1()
        {
            TestPayload();
        }

        [TestMethod]
        public void ScopingNotFound1()
        {
            TestPayload();
        }

        [TestMethod]
        public void CustomPeopleType1()
        {
            TestPayload();
        }

        [TestMethod]
        public void SportsScore1()
        {
            TestPayload();
        }

        [TestMethod]
        public void DataOnSource1()
        {
            TestPayload();
        }

        [TestMethod]
        public void ArraySelectors1()
        {
            TestPayload();
        }

        [TestMethod]
        public void IndexValueDefaults1()
        {
            TestPayload();
        }

        [TestMethod]
        public void IndexValues1()
        {
            TestPayload();
        }

        [TestMethod]
        public void IndexValues2()
        {
            TestPayload();
        }

        [TestMethod]
        public void RootData1()
        {
            TestPayload();
        }

        [TestMethod]
        public void RootData2()
        {
            TestPayload();
        }

        [TestMethod]
        public void When1()
        {
            TestPayload();
        }

        [TestMethod]
        public void When2()
        {
            TestPayload();
        }

        [TestMethod]
        public void When3()
        {
            TestPayload();
        }

        [TestMethod]
        public void EqualOperator1()
        {
            TestPayload();
        }

        [TestMethod]
        public void EqualOperator2()
        {
            TestPayload();
        }

        [TestMethod]
        public void StringLiterals1()
        {
            TestPayload();
        }

        [TestMethod]
        public void StringLiteralEscapeSequence1()
        {
            TestPayload();
        }

        [TestMethod]
        public void NullLiterals1()
        {
            TestPayload();
        }

        [TestMethod]
        public void BoolLiterals1()
        {
            TestPayload();
        }

        [TestMethod]
        public void IntLiterals1()
        {
            TestPayload();
        }

        [TestMethod]
        public void DoubleLiterals1()
        {
            TestPayload();
        }

        [TestMethod]
        public void CardDateFunctions()
        {
            TestPayload();
        }

        [TestMethod]
        public void AdditiveOperators1()
        {
            TestPayload();
        }

        [TestMethod]
        public void MultiplicativeOperators1()
        {
            TestPayload();
        }

        [TestMethod]
        public void InvalidExpressions1()
        {
            TestPayload();
        }

        private void TestPayload([CallerMemberName]string payloadName = null)
        {
            var parsed = JObject.Parse(File.ReadAllText(Directory.GetCurrentDirectory() + "\\TestPayloads\\" + payloadName + ".json"));

            AssertTransform(parsed["inputJson"], parsed["inputData"], parsed["expected"], payloadName);
        }

        private void AssertTransform(JToken inputJson, JToken inputData, JToken expected, string testCaseName)
        {
            JToken actual = JsonTransformer.Transform(inputJson, inputData, new Dictionary<string, JToken>());

            Assert.AreEqual(expected.ToString(), actual?.ToString());
        }
    }
}
