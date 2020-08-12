package io.adaptivecards.objectmodel;

import android.support.test.InstrumentationRegistry;
import android.util.Pair;
import android.widget.EditText;

import junit.framework.Assert;

import org.junit.Test;

import java.util.ArrayList;
import java.util.Date;

import io.adaptivecards.renderer.inputhandler.DateInputHandler;
import io.adaptivecards.renderer.inputhandler.NumberInputHandler;

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
                "\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
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

    @Test
    public void MinValidationTest() throws Exception
    {
        DateInput dateInput = TestUtil.createMockDateInput();
        dateInput.SetMin(c_inRangeDateValues[0]);

        DateInputHandler dateInputHandler = new DateInputHandler(dateInput, null);
        dateInputHandler.setView(new EditText(InstrumentationRegistry.getContext()));

        // Validate that empty input is always valid
        Assert.assertEquals(true, dateInputHandler.isValid());

        // Validate only min
        TestUtil.SpecificsValidationExecutor specsExecutor = new TestUtil.SpecificsValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_smallDateValues, false, specsExecutor);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_inRangeDateValues, c_largeDateValues), true, specsExecutor);

        // Validate non-required + min
        TestUtil.GeneralValidationExecutor gralExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_smallDateValues, false, gralExecutor);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_inRangeDateValues, c_largeDateValues), true, gralExecutor);
    }

    @Test
    public void MaxValidationTest() throws Exception
    {
        DateInput dateInput = TestUtil.createMockDateInput();
        dateInput.SetMax(c_inRangeDateValues[c_inRangeDateValues.length - 1]);

        DateInputHandler dateInputHandler = new DateInputHandler(dateInput, null);
        dateInputHandler.setView(new EditText(InstrumentationRegistry.getContext()));

        // Validate that empty input is always valid
        Assert.assertEquals(true, dateInputHandler.isValid());

        // Validate only max
        TestUtil.SpecificsValidationExecutor specsExecutor = new TestUtil.SpecificsValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallDateValues, c_inRangeDateValues), true, specsExecutor);
        TestUtil.runValidationTests(c_largeDateValues, false, specsExecutor);

        // Validate non-required + max
        TestUtil.GeneralValidationExecutor gralExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallDateValues, c_inRangeDateValues), true, gralExecutor);
        TestUtil.runValidationTests(c_largeDateValues, false, gralExecutor);
    }

    @Test
    public void MinMaxValidationTest() throws Exception
    {
        DateInput dateInput = TestUtil.createMockDateInput();
        dateInput.SetMin(c_inRangeDateValues[0]);
        dateInput.SetMax(c_inRangeDateValues[c_inRangeDateValues.length - 1]);

        DateInputHandler dateInputHandler = new DateInputHandler(dateInput, null);
        dateInputHandler.setView(new EditText(InstrumentationRegistry.getContext()));

        // Validate that empty input is always valid
        Assert.assertEquals(true, dateInputHandler.isValid());

        // Validate min + max
        TestUtil.SpecificsValidationExecutor specsExecutor = new TestUtil.SpecificsValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_smallDateValues, false, specsExecutor);
        TestUtil.runValidationTests(c_inRangeDateValues, true, specsExecutor);
        TestUtil.runValidationTests(c_largeDateValues, false, specsExecutor);

        // Validate min + max + non-required
        TestUtil.GeneralValidationExecutor gralExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_smallDateValues, false, gralExecutor);
        TestUtil.runValidationTests(c_inRangeDateValues, true, gralExecutor);
        TestUtil.runValidationTests(c_largeDateValues, false, gralExecutor);

        TestUtil.runValidationTests(c_invalidDateValues, true, gralExecutor);
    }

    @Test
    public void isRequiredValidation()
    {
        DateInput dateInput = TestUtil.createMockDateInput();
        dateInput.SetIsRequired(true);

        DateInputHandler dateInputHandler = new DateInputHandler(dateInput, null);
        dateInputHandler.setView(new EditText(InstrumentationRegistry.getContext()));

        TestUtil.GeneralValidationExecutor gralExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);

        // Validate that empty input is always invalid
        Assert.assertEquals(false, dateInputHandler.isValid());

        // Validate required
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallDateValues, c_inRangeDateValues, c_largeDateValues), true, gralExecutor);
    }

    private final String[] c_smallDateValues = {"1994-07-24", "1995-05-18", "1995-05-26", "1996-11-26", "1996-11-29", "1997-08-30", "1998-03-09"};
    private final String[] c_inRangeDateValues = {"1998-03-10", "1999-03-03", "1999-11-08", "2002-01-21", "2005-03-22", "2005-10-21", "2007-09-05"};
    private final String[] c_largeDateValues = {"2007-09-06", "2010-09-14", "2011-08-30", "2011-10-19", "2017-10-21", "2017-11-07", "2018-08-14"};
    private final String[] c_invalidDateValues = {"aWord", "12-12-2012", "12:02", "2011/08/30", "2013-13-13", "a-b-c", "7."};

    private final String c_defaultInputDate = "{\"id\":\"id\",\"type\":\"Input.Date\"}\n";
    private final String[] c_dateInputTests = {"0000-01-01", "1521-08-13", "1776-07-04", "1917-03-08", "1975-04-04", "1993-02-04", "2019-06-18", "2552-08-30"};
}
