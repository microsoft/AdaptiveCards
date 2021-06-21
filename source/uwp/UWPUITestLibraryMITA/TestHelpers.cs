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

        public static UIObject FindDescendantBy(string propertyName, string value, UIObject parent)
        {
            return parent.Descendants.Find(UIProperty.Get(propertyName), value);
        }

        public static UIObject FindElementByName(string name)
        {
            return FindDescendantBy("Name", name, Application.Instance.CoreWindow);
        }

        public static UIObject FindElementByClassName(string classname)
        {
            return FindDescendantBy("ClassName", classname, Application.Instance.CoreWindow);
        }

        public static UIObject FindElementByAutomationId(string automationId)
        {
            return FindDescendantBy("AutomationId", automationId, Application.Instance.CoreWindow);
        }

        public static UIObject FindElementByName(string name, UIObject parent)
        {
            return FindDescendantBy("Name", name, parent);
        }

        public static UIObject FindElementByClassName(string classname, UIObject parent)
        {
            return FindDescendantBy("ClassName", classname, parent);
        }

        public static UIObject FindElementByAutomationId(string automationId, UIObject parent)
        {
            return FindDescendantBy("AutomationId", automationId, parent);
        }

        public static UIObject FindFlyoutByAutomationId(string automationId)
        {
            return Application.Instance.CoreWindow.Parent.Descendants.Find(automationId);
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
            TextBlock titleTextBlock = CastTo<TextBlock>(uiObject);
            return titleTextBlock?.DocumentText;
        }

        public static string GetInputValue(string inputId)
        {
            var inputTextBlock = CastTo<TextBlock>(FindElementByName(inputId + "_retrievedValue"));
            return inputTextBlock?.DocumentText;
        }

        public static T CastTo<T>(UIObject uiObject)
        {
            return (T)Activator.CreateInstance(typeof(T), uiObject);
        }
    }
}
