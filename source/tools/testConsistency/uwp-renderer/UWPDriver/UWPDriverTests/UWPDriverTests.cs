// Copyright (c) Microsoft Corporation. All rights reserved. 
// Licensed under the MIT License. 

//To run these tests, create a directory TestFiles in the AppX folder and paste the sample cards there
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Microsoft.VisualStudio.TestTools.UnitTesting.Logging;
using Newtonsoft.Json.Linq;
using RestSharp;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using Windows.Storage;
namespace UWPDriverTest
{
    [TestClass]
    public class UWPDriverTests
    {
        
        [DataTestMethod]
        [DynamicData(nameof(GetVersionZeroFiles), DynamicDataSourceType.Method)]
        public void TestVersionZeroFiles(string file)
        {
            TestCardPayLoad(file);
        }

        [DataTestMethod]
        [DynamicData(nameof(GetVersionOneFiles), DynamicDataSourceType.Method)]
        public void TestVersionOneFiles(string file)
        {
            TestCardPayLoad(file);
        }

        [DataTestMethod]
        [DynamicData(nameof(GetVersionTwoFiles), DynamicDataSourceType.Method)]
        public void TestVersionTwoFiles(string file)
        {
            TestCardPayLoad(file);
        }

        [DataTestMethod]
        [DynamicData(nameof(GetVersionThreeFiles), DynamicDataSourceType.Method)]
        public void TestVersionThreeFiles(string file)
        {
            TestCardPayLoad(file);
        }

        private void TestCardPayLoad(string file)
        {
            Logger.LogMessage(string.Format("Testing File: {0}", file));
            JObject cardPayLoad = new JObject();
            cardPayLoad.Add("data", "");
            string cardTemplate = File.ReadAllText(file);
            Logger.LogMessage(string.Format("Successfully Read File: {0} size of string: {1}", file, cardTemplate.Length));
            Assert.AreNotEqual(0, cardTemplate.Length);
            cardPayLoad.Add("template", cardTemplate);
            RestClient client = new RestClient("http://10.64.36.176:8800/");
            client.Timeout = -1;
            RestRequest request = new RestRequest(Method.POST);
            request.AddHeader("Content-Type", "application/json");
            request.AddParameter("application/json", cardPayLoad.ToString(), ParameterType.RequestBody);
            IRestResponse response = client.Execute(request);
            Logger.LogMessage("Response: ", response.StatusCode);
            Assert.AreEqual(HttpStatusCode.OK, response.StatusCode);
            string result = response.Content;
            Assert.IsNotNull(result);
            JObject resJson = JObject.Parse(result);
            if (successfullyRendered(resJson))
            {
                Assert.IsTrue(isValidBase64(resJson));
            }
            else
            {
                Assert.IsTrue(errorListisNotEmpty(resJson));
            }
        }

        public static IEnumerable<object[]> GetVersionZeroFiles()
        {
            var scenarios = GetData("TestFiles\\samples\\v1.0\\Scenarios");
            var tests = GetData("TestFiles\\samples\\v1.0\\Tests");
            return scenarios.Concat(tests);
        }


        public static IEnumerable<object[]> GetVersionOneFiles()
        {
            var scenarios = GetData("TestFiles\\samples\\v1.1\\Scenarios");
            var tests = GetData("TestFiles\\samples\\v1.1\\Tests");
            return tests;
        }

        public static IEnumerable<object[]> GetVersionTwoFiles()
        {
            var scenarios = GetData("TestFiles\\samples\\v1.2\\Scenarios");
            var tests = GetData("TestFiles\\samples\\v1.2\\Tests");
            return scenarios.Concat(tests);
        }
        public static IEnumerable<object[]> GetVersionThreeFiles()
        {
           return GetData("TestFiles\\samples\\v1.3\\Tests");
        }
        public static IEnumerable<object[]> GetData(string payLoadPath)
        {
            foreach (var jsonFile in Directory.GetFiles(payLoadPath, "*.json", SearchOption.AllDirectories))
            {
                yield return new object[] { jsonFile };
            }

        }

        private bool isValidBase64(JObject result)
        {
            try
            {
                string imgStr = result.GetValue("imageData").ToString();
                byte[] imgArr = Convert.FromBase64String(imgStr);
                string converted = Convert.ToBase64String(imgArr);
                return imgStr.Equals(converted);
            }
            catch (Exception e)
            {
                return false;
            }
        }

        private bool successfullyRendered(JObject result)
        {
            string img = result.GetValue("imageData").ToString();
            return (img != null && img.Length != 0);
        }

        private bool errorListisNotEmpty(JObject result)
        {
            JArray errorList = JArray.Parse(result.GetValue("errors").ToString());
            JArray warnngList = JArray.Parse(result.GetValue("warnings").ToString());
            return errorList.Count != 0;
        }
    }
}
