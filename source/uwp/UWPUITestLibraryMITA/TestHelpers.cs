using Microsoft.Windows.Apps.Test.Foundation;
using Microsoft.Windows.Apps.Test.Foundation.Controls;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UWPUITestLibraryMITA
{
    public class TestHelpers
    {

        public static UIObject FindElementByName(string name)
        {
            return Application.Instance.CoreWindow.Descendants.Find(UIProperty.Get("Name"), name);
        }

        public static UIObject FindElementByClassName(string classname)
        {
            return Application.Instance.CoreWindow.Descendants.Find(UIProperty.Get("ClassName"), classname);
        }

        public static UIObject FindElementByAutomationId(string automationId)
        {
            var descendants = Application.Instance.CoreWindow.Parent.Descendants;
            return descendants.Find(automationId);
            // return Application.Instance.CoreWindow.Descendants.Find(UIProperty.Get("AutomationId"), automationId);
        }

        public static void GoToTestCase(string testCaseName)
        {
            var application = Application.Instance.CoreWindow;
            
            // If we are not in the home screen then we go to home and then click on the TestCase
            if (GetTitleText() != "Home")
            {
                FindElementByName("HomeButton")?.Click();
            }

            FindElementByName(testCaseName)?.Click();

            if (GetTitleText() != testCaseName)
            {
                throw new Exception("TestCase " + testCaseName + "could not be initialized");
            }
        }

        private static string GetTitleText()
        {
            var uiObject = FindElementByName("TitleTextBlock");
            TextBlock titleTextBlock = (TextBlock)Activator.CreateInstance(typeof(TextBlock), uiObject);
            return titleTextBlock?.DocumentText;
        }

        public static string GetInputValue(string inputId)
        {
            var inputTextBlock = (TextBlock)FindElementByName(inputId + "_retrievedValue");
            return inputTextBlock?.DocumentText;
        }
    }
}
