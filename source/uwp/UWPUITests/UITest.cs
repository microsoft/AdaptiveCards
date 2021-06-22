// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

namespace UWPUITests
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
