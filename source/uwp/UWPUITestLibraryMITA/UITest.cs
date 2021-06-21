using Microsoft.VisualStudio.TestTools.UnitTesting;
using Microsoft.Windows.Apps.Test.Foundation;
using Microsoft.Windows.Apps.Test.Foundation.Controls;
using System;
using System.Threading;
using Windows.UI.Xaml.Tests.MUXControls.InteractionTests.Common;

namespace UWPUITestLibraryMITA
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
        public void ActivityUpdateSmokeTest()
        {
            TestHelpers.GoToTestCase("ActivityUpdate");

            var showCardButton = TestHelpers.FindElementByName("Set due date");
            Assert.IsNotNull(showCardButton, "Could not find 'Set due date' button");
            showCardButton.Click();

            var dateInput = TestHelpers.FindElementByClassName("CalendarDatePicker");
            dateInput.Click();

            var calendarView = TestHelpers.FindFlyoutByAutomationId("CalendarView");
            TestHelpers.FindElementByAutomationId("NextButton", calendarView).Click();
            Thread.Sleep(1000);
            TestHelpers.FindElementByName("16", calendarView).Click();

            var commentTextBox = TestHelpers.CastTo<Edit>(TestHelpers.FindElementByName("Add a comment"));
            commentTextBox.SendKeys("A comment");

            TestHelpers.FindElementByName("OK").Click();

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
