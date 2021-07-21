using Microsoft.Windows.Apps.Test.Foundation;
using Microsoft.Windows.Apps.Test.Foundation.Controls;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json;

namespace UWPUITests
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

        public static UIObject FindByMultiple(params object[] list)
        {
            var filteredList = Application.Instance.CoreWindow.Descendants;

            for (int i = 0; (i + 1) < list.Length && filteredList.Count > 1; i += 2)
            {
                string propertyName = list[i] as string;
                string value = list[i + 1] as string;
                filteredList = filteredList.FindMultiple(UIProperty.Get(propertyName), value);
            }

            return filteredList.Count > 0 ? filteredList[0] : null;
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
            var inputTextBlock = CastTo<TextBlock>(FindElementByName("RetrievedInputs_TextBlock"));
            Assert.IsNotNull(inputTextBlock, "Failed to retrieve retrieved inputs text block");

            string retrivedInputsJsonString = inputTextBlock.DocumentText;
            var retrievedInputs = JsonConvert.DeserializeObject<Dictionary<string, string>>(retrivedInputsJsonString);

            return retrievedInputs[inputId];

            // var inputTextBlock = CastTo<TextBlock>(FindElementByName(inputId + "_retrievedValue"));
            // return inputTextBlock?.DocumentText;
        }

        public static void SetDateToUIElement(int year, int month, int day)
        {
            // Retrieve the date input and click on it
            // TODO: Fix UWP implementation to assign name/id to the CalendarDatePicker control
            var dateInput = FindElementByClassName("CalendarDatePicker");
            dateInput.Click();

            // Retrieve the popup which contains the calendar view
            var calendarView = FindFlyoutByAutomationId("CalendarView");

            UIObject headerButton = CastTo<Button>(FindElementByAutomationId("HeaderButton", calendarView));
            string[] monthAndYear = headerButton.Name.Split(" ");

            // The CalendarDatePicker control adds a character 8206 to each end of the month name,
            // so we have to remove them before looking up for the month number
            int currentMonth = MonthNameToInt(monthAndYear[0]);
            MoveToMonth(currentMonth, month, calendarView);
            
            // Click on the day "16" button which in turn closes the popup
            FindElementByName("16", calendarView).Click();
        }

        private static void MoveToMonth(int currentMonth, int expectedMonth, UIObject calendarView)
        {
            if (currentMonth < expectedMonth)
            {
                UIObject nextButton = FindElementByAutomationId("NextButton", calendarView);
                while (currentMonth != expectedMonth)
                {
                    nextButton.Click();
                    currentMonth++;
                }
            }
            if (currentMonth > expectedMonth)
            {
                UIObject previousButton = FindElementByAutomationId("PreviousButton", calendarView);
                while (currentMonth != expectedMonth)
                {
                    previousButton.Click();
                    currentMonth--;
                }
            }

            // Wait for the scrolling animation to end
            Thread.Sleep(1000);
        }

        static int MonthNameToInt(string monthName)
        {
            monthName = monthName.Substring(1, monthName.Length - 2);
            return DateTime.ParseExact(monthName, "MMMM", CultureInfo.CurrentCulture).Month;
        }

        public static T CastTo<T>(UIObject uiObject)
        {
            return (T)Activator.CreateInstance(typeof(T), uiObject);
        }
    }
}
