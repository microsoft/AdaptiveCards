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
        {
            final String inputDateDefaultMax = "{\"id\":\"id\",\"type\":\"Input.Date\"}\n";

            DateInput dateInput = TestUtil.createMockDateInput();
            dateInput.SetMax("");
            Assert.assertEquals(inputDateDefaultMax, dateInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputDateDefaultMax), "1.0");
            DateInput parsedDateInput = TestUtil.castToDateInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedDateInput.GetMax());
        }

        {
            final String inputNumberMaxTemplate =
                "{\"id\":\"id\",\"max\":\"%s\",\"type\":\"Input.Date\"}\n";
            String[] tests = {"0000-01-01", "1521-08-13", "1776-07-04", "1917-03-08", "1975-04-04", "1993-02-04", "2019-06-18", "2552-08-30"};

            for (int i = 0; i < tests.length; ++i)
            {
                String maxJson = String.format(inputNumberMaxTemplate, tests[i]);

                DateInput dateInput = TestUtil.createMockDateInput();
                dateInput.SetMax(tests[i]);
                Assert.assertEquals(maxJson, dateInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(maxJson), "1.0");
                DateInput parsedDateInput = TestUtil.castToDateInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedDateInput.GetMax());
            }
        }
    }

    @Test
    public void MinTest() throws Exception
    {
        {
            final String inputDateDefaultMax = "{\"id\":\"id\",\"type\":\"Input.Date\"}\n";

            DateInput dateInput = TestUtil.createMockDateInput();
            dateInput.SetMin("");
            Assert.assertEquals(inputDateDefaultMax, dateInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputDateDefaultMax), "1.0");
            DateInput parsedDateInput = TestUtil.castToDateInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedDateInput.GetMin());
        }

        {
            final String inputNumberMaxTemplate =
                "{\"id\":\"id\",\"min\":\"%s\",\"type\":\"Input.Date\"}\n";
            String[] tests = {"0000-01-01", "1521-08-13", "1776-07-04", "1917-03-08", "1975-04-04", "1993-02-04", "2019-06-18", "2552-08-30"};

            for (int i = 0; i < tests.length; ++i)
            {
                String maxJson = String.format(inputNumberMaxTemplate, tests[i]);

                DateInput dateInput = TestUtil.createMockDateInput();
                dateInput.SetMin(tests[i]);
                Assert.assertEquals(maxJson, dateInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(maxJson), "1.0");
                DateInput parsedDateInput = TestUtil.castToDateInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedDateInput.GetMin());
            }
        }
    }

    @Test
    public void PlaceholderTest() throws Exception
    {
        {
            final String inputDateDefaultPlaceholder = "{\"id\":\"id\",\"type\":\"Input.Date\"}\n";

            DateInput dateInput = TestUtil.createMockDateInput();
            dateInput.SetPlaceholder("");
            Assert.assertEquals(inputDateDefaultPlaceholder, dateInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputDateDefaultPlaceholder), "1.0");
            DateInput parsedDateInput = TestUtil.castToDateInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedDateInput.GetPlaceholder());
        }

        {
            final String inputTextPlaceholderTemplate = "{\"id\":\"id\",\"placeholder\":\"%s\",\"type\":\"Input.Date\"}\n";
            String tests[] = {"Sample text",
                "This is just a little bit tiny teeny bit larger than the one before this one a.k.a. index [0]",
                "The quick brown fox jumps over the lazy dog",
                "{{DATE(2017-02-14T06:08:39Z,LONG)}}",
                "This is some **bold** text"};

            for (int i = 0; i < tests.length; ++i)
            {
                String inputTextPlaceholderJson = String.format(inputTextPlaceholderTemplate, tests[i]);

                DateInput dateInput = TestUtil.createMockDateInput();
                dateInput.SetPlaceholder(tests[i]);
                Assert.assertEquals(inputTextPlaceholderJson, dateInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTextPlaceholderJson), "1.0");
                DateInput parsedDateInput = TestUtil.castToDateInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedDateInput.GetPlaceholder());
            }
        }
    }

    @Test
    public void ValueTest() throws Exception
    {
        {
            final String inputDateDefaultPlaceholder = "{\"id\":\"id\",\"type\":\"Input.Date\"}\n";

            DateInput dateInput = TestUtil.createMockDateInput();
            dateInput.SetValue("");
            Assert.assertEquals(inputDateDefaultPlaceholder, dateInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputDateDefaultPlaceholder), "1.0");
            DateInput parsedDateInput = TestUtil.castToDateInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedDateInput.GetValue());
        }

        {
            final String inputDatePlaceholderTemplate = "{\"id\":\"id\",\"type\":\"Input.Date\",\"value\":\"%s\"}\n";
            String tests[] = {"Sample text",
                "This is just a little bit tiny teeny bit larger than the one before this one a.k.a. index [0]",
                "The quick brown fox jumps over the lazy dog",
                "{{DATE(2017-02-14T06:08:39Z,LONG)}}",
                "This is some **bold** text"};

            for (int i = 0; i < tests.length; ++i)
            {
                String inputDatePlaceholderJson = String.format(inputDatePlaceholderTemplate, tests[i]);

                DateInput dateInput = TestUtil.createMockDateInput();
                dateInput.SetValue(tests[i]);
                Assert.assertEquals(inputDatePlaceholderJson, dateInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputDatePlaceholderJson), "1.0");
                DateInput parsedDateInput = TestUtil.castToDateInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedDateInput.GetValue());
            }
        }
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

}
