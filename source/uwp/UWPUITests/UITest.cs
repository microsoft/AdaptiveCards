// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Threading;

namespace UWPUITests
{
    [TestClass]
    public class UITest
    {
        protected static Application application = null;

        [ClassInitialize]
        public static void Setup(TestContext testContext)
        {
            application = Application.Instance;
            application.Initialize();
        }

        [TestMethod]
        public void SmokeTestActivityUpdateCard()
        {
            TestHelpers.GoToTestCase("ActivityUpdate");

            Thread.Sleep(1000);

            var appSession = application.TestAppSession;

            var showCardButton = appSession.FindElementByName("Set due date");
            Assert.IsNotNull(showCardButton, "Could not find 'Set due date' button");
            showCardButton.Click();

            var dateInput = appSession.FindElementByClassName("CalendarDatePicker");
            dateInput.Click();

            var calendarView = appSession.FindElementByAccessibilityId("CalendarView");
            calendarView.FindElementByAccessibilityId("NextButton").Click();
            calendarView.FindElementByName("16").Click();

            var commentTextBox = appSession.FindElementByName("Add a comment");
            commentTextBox.Clear();
            commentTextBox.SendKeys("A comment");

            appSession.FindElementByName("OK").Click();

            Assert.AreEqual("A comment", TestHelpers.GetInputValue("comment"), "Values for input comment differ");
            Assert.AreEqual("2021-07-16", TestHelpers.GetInputValue("dueDate"), "Values for input dueDate differ");
        }

        [ClassCleanup]
        public static void TearDown()
        {
            application.Close();
        }
    }
}
