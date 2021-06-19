using Microsoft.VisualStudio.TestTools.UnitTesting;
using Microsoft.Windows.Apps.Test.Foundation;
using Microsoft.Windows.Apps.Test.Foundation.Controls;
using Windows.UI.Xaml.Tests.MUXControls.InteractionTests.Common;

namespace UWPUITestLibraryMITA
{
    [TestClass]
    public class UnitTest1
    {
        protected static Application application = null;

        [ClassInitialize]
        public static void Setup(TestContext testContext)
        {
            application = Application.Instance;
            application.Initialize();
        }

        [TestMethod]
        public void TestMethod1()
        {
            TestHelpers.GoToTestCase("ActivityUpdate");

            var showCardButton = TestHelpers.FindElementByName("Set due date");
            Assert.IsNotNull(showCardButton, "Could not find 'Set due date' button");
            showCardButton.Click();

            var dateInput = TestHelpers.FindElementByClassName("CalendarDatePicker");
            dateInput.Click();

            var calendarView = TestHelpers.FindElementByAutomationId("CalendarView");
            TestHelpers.FindElementByAutomationId("NextButton").Click();
            TestHelpers.FindElementByName("16").Click();

            var commentTextBox = (Edit)TestHelpers.FindElementByName("Add a comment");
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
