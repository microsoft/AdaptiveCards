using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UWPUITestLibrary
{
    public class TestHelpers
    {

        public static void GoToTestCase(string testCaseName)
        {
            var appSession = Application.Instance.TestAppSession;

            // If we are not in the home screen then we go to home and then click on the TestCase
            if (GetTitleText() != "Home")
            {
                appSession.FindElementByName("HomeButton")?.Click();
            }

            appSession.FindElementByName(testCaseName)?.Click();

            if (GetTitleText() != testCaseName)
            {
                throw new Exception("TestCase " + testCaseName + "could not be initialized");
            }    
        }

        private static string GetTitleText()
        {
            var titleTextBlock = Application.Instance.TestAppSession.FindElementByName("TitleTextBlock");
            return titleTextBlock?.Text;
        }

        public static string GetInputValue(string inputId)
        {
            var inputTextBlock = Application.Instance.TestAppSession.FindElementByName(inputId + "_retrievedValue");
            return inputTextBlock.Text;
        }

    }
}
