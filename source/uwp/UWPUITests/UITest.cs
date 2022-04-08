using Microsoft.VisualStudio.TestTools.UnitTesting;
using Microsoft.Windows.Apps.Test.Foundation.Controls;
using Microsoft.Windows.Apps.Test.Automation;

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
            TestHelpers.SetDateToUIElement(7, 16);

            // Retrieve the "Add a comment" Input.Text and fill it with information
            var commentTextBox = TestHelpers.CastTo<Edit>(TestHelpers.FindElementByName("Add a comment"));
            commentTextBox.SendKeys("A comment");

            // Submit data
            TestHelpers.FindElementByName("OK").Click();

            // Verify submitted data
            Assert.AreEqual("A comment", TestHelpers.GetInputValue("comment"), "Values for input comment differ");
            Assert.AreEqual(System.DateTime.Now.Year.ToString() + "-07-16", TestHelpers.GetInputValue("dueDate"), "Values for input dueDate differ");
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

        [TestMethod]
        public void InputToggleTests()
        {
            TestHelpers.GoToTestCase("Input.Toggle");

            var checkBoxUIElement = TestHelpers.FindByMultiple(
                "Name", "Please check the box below to accept the terms and agreements: *\r\n",
                "ClassName", "CheckBox");
            Assert.IsNotNull(checkBoxUIElement);

            var checkBox = TestHelpers.CastTo<CheckBox>(checkBoxUIElement);

            Assert.AreEqual(ToggleState.On, checkBox.ToggleState);

            var label = TestHelpers.FindElementByName("Please check the box below to accept the terms and agreements: *\r\n");
            Assert.IsNotNull(label);

            checkBox.Toggle();
            Assert.AreEqual(ToggleState.Off, checkBox.ToggleState);

            var submitButton = TestHelpers.FindElementByName("OK");
            submitButton.Click();

            var errorMessage = TestHelpers.FindElementByName("You must accept the terms to continue.");
            Assert.IsNotNull(errorMessage);

            checkBox.Toggle();
            Assert.AreEqual(ToggleState.On, checkBox.ToggleState);
            submitButton.Click();

            Assert.AreEqual("true", TestHelpers.GetInputValue("acceptTerms"));
        }

        [TestMethod]
        public void SecondaryShowCardTest()
        {
            TestHelpers.GoToTestCase("PrimarySecondaryShowCards");

            // We should be able to find the primary show card action and the overflow menu
            var primaryShowCardAction = TestHelpers.FindByMultiple("Name", "Primary Show Card Action", "ClassName", "Button");
            Assert.IsNotNull(primaryShowCardAction);

            var overflowMenu = TestHelpers.FindByMultiple("Name", "...", "ClassName", "Button");
            Assert.IsNotNull(overflowMenu);

            // We should not be able to find either of the show cards
            Assert.ThrowsException<Microsoft.Windows.Apps.Test.Foundation.UIObjectNotFoundException>(delegate () { TestHelpers.FindElementByName("Primary Show Card"); });
            Assert.ThrowsException<Microsoft.Windows.Apps.Test.Foundation.UIObjectNotFoundException>(delegate () { TestHelpers.FindElementByName("Secondary Show Card"); });

            // Click the primary show card and validate that the card appears
            primaryShowCardAction.Click();

            var primaryShowCard = TestHelpers.FindElementByName("Primary Show Card");
            Assert.IsNotNull(primaryShowCard);
            Assert.ThrowsException<Microsoft.Windows.Apps.Test.Foundation.UIObjectNotFoundException>(delegate () { TestHelpers.FindElementByName("Secondary Show Card"); });

            // Click the overflow menu and find the secondary show card action
            overflowMenu.Click();

            var secondaryShowCardAction = TestHelpers.FindPopupByName("Secondary Show Card Action");
            Assert.IsNotNull(secondaryShowCardAction);

            // Click the secondary action and validate that the card appears
            secondaryShowCardAction.Click();

            var secondaryShowCard = TestHelpers.FindElementByName("Secondary Show Card");
            Assert.ThrowsException<Microsoft.Windows.Apps.Test.Foundation.UIObjectNotFoundException>(delegate () { TestHelpers.FindElementByName("Primary Show Card"); });

            // Close the secondary show card and validate the state
            overflowMenu.Click();
            secondaryShowCardAction = TestHelpers.FindPopupByName("Secondary Show Card Action");
            Assert.IsNotNull(secondaryShowCardAction);
            secondaryShowCardAction.Click();

            primaryShowCardAction = TestHelpers.FindByMultiple("Name", "Primary Show Card Action", "ClassName", "Button");
            Assert.IsNotNull(primaryShowCardAction);

            overflowMenu = TestHelpers.FindByMultiple("Name", "...", "ClassName", "Button");
            Assert.IsNotNull(overflowMenu);

            Assert.ThrowsException<Microsoft.Windows.Apps.Test.Foundation.UIObjectNotFoundException>(delegate () { TestHelpers.FindElementByName("Primary Show Card"); });
            Assert.ThrowsException<Microsoft.Windows.Apps.Test.Foundation.UIObjectNotFoundException>(delegate () { TestHelpers.FindElementByName("Secondary Show Card"); });
        }

        [TestMethod]
        public void PasswordTest()
        {
            TestHelpers.GoToTestCase("Input.Text.PasswordStyle");

            var passwordBox = TestHelpers.CastTo<Edit>(TestHelpers.FindByMultiple(
                "Name", "Input.Text With Password Style\r\n",
                "ClassName", "PasswordBox"));

            Assert.IsTrue(passwordBox.IsPassword);

            passwordBox.SetValue("aNewPassword123!");
            Assert.AreEqual("●●●●●●●●●●●●●●●●", passwordBox.Value);

            // Submit data
            TestHelpers.FindElementByName("OK").Click();

            // Verify submitted data
            Assert.AreEqual("aNewPassword123!", TestHelpers.GetInputValue("id0"));
        }

        [TestMethod]
        public void PasswordRegexTest()
        {
            TestHelpers.GoToTestCase("Input.Text.PasswordStyle");

            var passwordBox = TestHelpers.CastTo<Edit>(TestHelpers.FindByMultiple(
                "Name", "Input.Text With Password Style\r\n",
                "ClassName", "PasswordBox"));

            Assert.IsTrue(passwordBox.IsPassword);

            passwordBox.SetValue("short");

            // Submit data
            TestHelpers.FindElementByName("OK").Click();

            var errorMessage = TestHelpers.FindElementByName("Password must be between 8 and 20 characters");
            Assert.IsNotNull(errorMessage);

            passwordBox.SetValue("LOOOONGER!");

            TestHelpers.FindElementByName("OK").Click();

            // Verify submitted data
            Assert.AreEqual("LOOOONGER!", TestHelpers.GetInputValue("id0"));
        }

        [ClassCleanup]
        public static void TearDown()
        {
            application.Close();
        }
    }

}
