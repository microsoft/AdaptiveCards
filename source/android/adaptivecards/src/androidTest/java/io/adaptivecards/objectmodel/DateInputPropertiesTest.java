package io.adaptivecards.objectmodel;

import android.util.Pair;

import junit.framework.Assert;

import org.junit.Test;

import java.util.ArrayList;
import java.util.Date;

import static org.junit.Assert.*;

public class DateInputPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest()
    {
        final String dateInputNoDefaultValues =
            "{\"errorMessage\":\"Error message\"," +
                "\"id\":\"id\"," +
                "\"label\":\"Input label\"," +
                "\"max\":\"2019-07-18\"," +
                "\"min\":\"2018-06-17\"," +
                "\"placeholder\":\"Sample placeholder\"," +
                "\"type\":\"Input.Date\"," +
                "\"value\":\"2019-01-01\"}\n";

        DateInput dateInput = TestUtil.createMockDateInput();
        dateInput.SetErrorMessage("Error message");
        dateInput.SetLabel("Input label");
        dateInput.SetMax("2019-07-18");
        dateInput.SetMin("2018-06-17");
        dateInput.SetPlaceholder("Sample placeholder");
        dateInput.SetValue("2019-01-01");

        Assert.assertEquals(dateInputNoDefaultValues, dateInput.Serialize());
    }

    @Test
    public void AllPropertiesWithInheritedTest()
    {
        final String dateInputNoDefaultValues =
            "{\"errorMessage\":\"Error message\"," +
                "{\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                "\"height\":\"Stretch\"," +
                "\"id\":\"id\"," +
                "\"isVisible\":false," +
                "\"label\":\"Input label\"," +
                "\"max\":\"2019-07-18\"," +
                "\"min\":\"2018-06-17\"," +
                "\"placeholder\":\"Sample placeholder\"," +
                "\"separator\":true," +
                "\"spacing\":\"medium\"," +
                "\"type\":\"Input.Date\"," +
                "\"value\":\"2019-01-01\"}\n";

        DateInput dateInput = TestUtil.createMockDateInput();
        dateInput.SetErrorMessage("Error message");
        dateInput.SetFallbackType(FallbackType.Content);
        dateInput.SetFallbackContent(TestUtil.createMockImage());
        dateInput.SetHeight(HeightType.Stretch);
        dateInput.SetIsVisible(false);
        dateInput.SetLabel("Input label");
        dateInput.SetMax("2019-07-18");
        dateInput.SetMin("2018-06-17");
        dateInput.SetPlaceholder("Sample placeholder");
        dateInput.SetSeparator(true);
        dateInput.SetSpacing(Spacing.Medium);
        dateInput.SetValue("2019-01-01");

        Assert.assertEquals(dateInputNoDefaultValues, dateInput.Serialize());
    }

    @Test
    public void MaxTest() throws Exception
    {
        DateInputCommand<String> c = new DateInputCommand<String>() {
            @Override
            public String get(DateInput element) { return element.GetMax(); }

            @Override
            public void set(String value, DateInput element) { element.SetMax(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputDate, "");

        final String inputNumberMaxTemplate = "{\"id\":\"id\",\"max\":\"%s\",\"type\":\"Input.Date\"}\n";
        TestUtil.executeTests(c, inputNumberMaxTemplate, c_dateInputTests);
    }

    @Test
    public void MinTest() throws Exception
    {
        DateInputCommand<String> c = new DateInputCommand<String>() {
            @Override
            public String get(DateInput element) { return element.GetMin(); }

            @Override
            public void set(String value, DateInput element) { element.SetMin(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputDate, "");

        final String inputNumberMinTemplate = "{\"id\":\"id\",\"min\":\"%s\",\"type\":\"Input.Date\"}\n";
        TestUtil.executeTests(c, inputNumberMinTemplate, c_dateInputTests);
    }

    @Test
    public void PlaceholderTest() throws Exception
    {
        DateInputCommand<String> c = new DateInputCommand<String>() {
            @Override
            public String get(DateInput element) { return element.GetPlaceholder(); }

            @Override
            public void set(String value, DateInput element) { element.SetPlaceholder(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputDate, "");

        final String inputTextPlaceholderTemplate = "{\"id\":\"id\",\"placeholder\":\"%s\",\"type\":\"Input.Date\"}\n";
        TestUtil.executeTests(c, inputTextPlaceholderTemplate, TestUtil.c_regularStringTestCases);
        TestUtil.executeTests(c, inputTextPlaceholderTemplate, TestUtil.c_dateStringTestCases);
    }

    @Test
    public void ValueTest() throws Exception
    {
        DateInputCommand<String> c = new DateInputCommand<String>() {
            @Override
            public String get(DateInput element) { return element.GetValue(); }

            @Override
            public void set(String value, DateInput element) { element.SetValue(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputDate, "");

        final String inputDateValueTemplate = "{\"id\":\"id\",\"type\":\"Input.Date\",\"value\":\"%s\"}\n";
        TestUtil.executeTests(c, inputDateValueTemplate, c_dateInputTests);
    }

    @Test
    public void LabelTest() throws Exception
    {
        DateInputCommand<String> c = new DateInputCommand<String>() {
            @Override
            public String get(DateInput element) { return element.GetLabel(); }

            @Override
            public void set(String value, DateInput element) { element.SetLabel(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputDate, "");

        final String inputDateLabelTemplate = "{\"id\":\"id\",\"label\":\"%s\",\"type\":\"Input.Date\"}\n";
        TestUtil.executeTests(c, inputDateLabelTemplate, TestUtil.c_regularStringTestCases);
    }

    @Test
    public void ErrorMessageTest() throws Exception
    {
        DateInputCommand<String> c = new DateInputCommand<String>() {
            @Override
            public String get(DateInput element) { return element.GetErrorMessage(); }

            @Override
            public void set(String value, DateInput element) { element.SetErrorMessage(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputDate, "");

        final String inputDateErrorMessageTemplate = "{\"errorMessage\":\"%s\",\"id\":\"id\",\"type\":\"Input.Date\"}\n";
        TestUtil.executeTests(c, inputDateErrorMessageTemplate, TestUtil.c_regularStringTestCases);
    }

    private abstract class DateInputCommand<E> implements TestUtil.Command<DateInput, E>
    {
        @Override
        public DateInput getMockObject()
        {
            return TestUtil.createMockDateInput();
        }

        @Override
        public DateInput castTo(BaseCardElement element) {
            return TestUtil.castToDateInput(element);
        }
    }

    private final String c_defaultInputDate = "{\"id\":\"id\",\"type\":\"Input.Date\"}\n";
    private final String[] c_dateInputTests = {"0000-01-01", "1521-08-13", "1776-07-04", "1917-03-08", "1975-04-04", "1993-02-04", "2019-06-18", "2552-08-30"};
}
