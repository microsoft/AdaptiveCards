using Microsoft.VisualStudio.TestTools.UnitTesting;
using Microsoft.Windows.Apps.Test.Foundation;
using Microsoft.Windows.Apps.Test.Foundation.Controls;
using System;
using System.Threading;
using Windows.UI.Xaml.Tests.MUXControls.InteractionTests.Common;

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
        public void ActivityUpdateSmokeTest()
        {
            TestHelpers.GoToTestCase("ActivityUpdate");

            // Retrieve the "Set due date" Button and click it
            var showCardButton = TestHelpers.FindElementByName("Set due date");
            Assert.IsNotNull(showCardButton, "Could not find 'Set due date' button");
            showCardButton.Click();

            // Set the date on the Date control
            TestHelpers.SetDateToUIElement(2021, 07, 16);

            // Retrieve the "Add a comment" Input.Text and fill it with information
            var commentTextBox = TestHelpers.CastTo<Edit>(TestHelpers.FindElementByName("Add a comment"));
            commentTextBox.SendKeys("A comment");

            // Submit data
            TestHelpers.FindElementByName("OK").Click();

            // Verify submitted data
            Assert.AreEqual("A comment", TestHelpers.GetInputValue("comment"), "Values for input comment differ");
            Assert.AreEqual("2021-07-16", TestHelpers.GetInputValue("dueDate"), "Values for input dueDate differ");
        }

        [TestMethod]
        public void InputTextValidationFailsForEmptyRequiredInputTest()
        {
            TestHelpers.GoToTestCase("Input.Text.ErrorMessage");

            // Click on 'Submit' button
            var showCardButton = TestHelpers.FindElementByName("Submit");
            Assert.IsNotNull(showCardButton, "Could not find 'Submit' button");
            showCardButton.Click();

            // Find the 'Required Input.Text' Input.Text,
            // as both the Label and the TextBox share the same name we have to discern between them
            var requiredInputTextBox = TestHelpers.FindByMultiple(
                "Name", "Required Input.Text *\r\n",
                "ClassName", "TextBox");

            // Verify the retrieved Input.Text has the keyboard focus
            Assert.IsTrue(requiredInputTextBox.HasKeyboardFocus, "The first textblock did not get focus");
        }

        [ClassCleanup]
        public static void TearDown()
        {
            application.Close();
        }
    }
}
