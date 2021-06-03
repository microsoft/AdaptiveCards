using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

namespace UWPUITestLibrary
{
    [TestClass]
    public class UITest
    {
        protected static Application application = null;

        [ClassInitialize]
        public static void Setup(TestContext testContext)
        {
            application = new Application();
            application.Initialize();
        }
    
        [TestMethod]
        public void TestMethod1()
        {
            Assert.IsTrue(true);
        }

        [ClassCleanup]
        public static void TearDown()
        {
            application.Close();
        }
    }
}
