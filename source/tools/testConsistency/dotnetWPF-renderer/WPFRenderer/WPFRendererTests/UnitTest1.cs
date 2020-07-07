using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.IO;
using Newtonsoft.Json.Linq;
using System.Text;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting.Logging;
using System.Drawing; 

namespace WPFRendererTests
{
    [TestClass]
    public class UnitTest1
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

        public void TestCardPayLoad(string file)
        {
            Logger.LogMessage(string.Format("Testing File: {0}", file));
            JObject cardPayLoad = new JObject();
            cardPayLoad.Add("data", "");
            string cardTemplate = File.ReadAllText(file);
            Logger.LogMessage(string.Format("Successfully Read File: {0} size of string: {1}", file, cardTemplate.Length));
            Assert.AreNotEqual(0, cardTemplate.Length);
            cardPayLoad.Add("template", cardTemplate);
            StringReader reader = new StringReader(cardPayLoad.ToString());
            Console.SetIn(reader);
            StringBuilder sb = new StringBuilder();
            StringWriter writer = new StringWriter(sb);
            Console.SetOut(writer);
            Assert.AreEqual(0, sb.Length);
            WPFRenderer.Program.Main();
            Assert.AreNotEqual(0, sb.Length);
            Logger.LogMessage(string.Format("The renderer returned a non-empty result json string of size: {0}", sb.Length));
            JObject result = JObject.Parse(sb.ToString());
            if (successfullyRendered(result))
            {
                Logger.LogMessage(string.Format("The card was successfully rendered. The warnings generated were: {0}", result["warnings"].ToString()));
                Logger.LogMessage(string.Format("The base64 encoded image is: {0}", result["imageData"].ToString()));
                Assert.IsTrue(isValidBase64(result));
            }
            else
            {
                Logger.LogMessage(string.Format("The card was not rendered successfully. The following were the errors: {0}", result["errors"].ToString()));
                Assert.IsTrue(errorListisNotEmpty(result));
            }
        }

        public static IEnumerable<object[]> GetVersionZeroFiles()
        {
            return GetData("..\\..\\..\\..\\..\\..\\..\\..\\samples\\v1.0");
        }


        public static IEnumerable<object[]> GetVersionOneFiles()
        {
            return GetData("..\\..\\..\\..\\..\\..\\..\\..\\samples\\v1.1");
        }

        public static IEnumerable<object[]> GetVersionTwoFiles()
        {
            return GetData("..\\..\\..\\..\\..\\..\\..\\..\\samples\\v1.2");
        }
        public static IEnumerable<object[]> GetVersionThreeFiles()
        {
            return GetData("..\\..\\..\\..\\..\\..\\..\\..\\samples\\v1.3");
        }
        public static IEnumerable<object[]> GetData(string payLoadPath)
        {
            foreach(var jsonFile in Directory.GetFiles(payLoadPath, "*.json", SearchOption.AllDirectories))
            {
                yield return new object[] { jsonFile };
            }
           
        }

        bool isValidBase64(JObject result)
        {
            try
            {
                string imgStr = result.GetValue("imageData").ToString();
                byte[] imgArr = Convert.FromBase64String(imgStr);
                Image image;
                using (MemoryStream ms = new MemoryStream(imgArr))
                {
                    image = Image.FromStream(ms);
                }

                return true;
            }
            catch(Exception e)
            {
                return false;
            }
        }

        bool errorListisNotEmpty(JObject result)
        {
            JArray errorList = JArray.Parse(result.GetValue("errors").ToString());
            JArray warnngList = JArray.Parse(result.GetValue("warnings").ToString());
            return errorList.Count != 0;
        }

        bool successfullyRendered(JObject result)
        {
            string img = result.GetValue("imageData").ToString();
            return (img!= null && img.Length != 0);
        }
        
    }
}
