package io.adaptivecards.objectmodel;

import android.util.Pair;

import junit.framework.Assert;

import org.junit.Test;

import java.sql.Time;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

import io.adaptivecards.renderer.input.TimeInputRenderer;
import io.adaptivecards.renderer.readonly.RendererUtil;

import static org.junit.Assert.*;

public class TimeInputPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest()
    {
        final String timeInputNoDefaultValues =
            "{\"id\":\"id\"," +
                "\"max\":\"23:59\"," +
                "\"min\":\"00:00\"," +
                "\"placeholder\":\"Sample placeholder\"," +
                "\"type\":\"Input.Time\"," +
                "\"value\":\"16:20\"}\n";

        TimeInput timeInput = TestUtil.createMockTimeInput();
        timeInput.SetMax("23:59");
        timeInput.SetMin("00:00");
        timeInput.SetPlaceholder("Sample placeholder");
        timeInput.SetValue("16:20");

        Assert.assertEquals(timeInputNoDefaultValues, timeInput.Serialize());
    }

    @Test
    public void AllPropertiesWithInheritedTest()
    {
        final String timeInputNoDefaultValues =
            "{\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                "\"height\":\"Stretch\"," +
                "\"id\":\"id\"," +
                "\"isVisible\":false," +
                "\"max\":\"21:59\"," +
                "\"min\":\"04:37\"," +
                "\"placeholder\":\"Sample placeholder\"," +
                "\"separator\":true," +
                "\"spacing\":\"medium\"," +
                "\"type\":\"Input.Time\"," +
                "\"value\":\"18:00\"}\n";

        TimeInput timeInput = TestUtil.createMockTimeInput();
        timeInput.SetFallbackType(FallbackType.Content);
        timeInput.SetFallbackContent(TestUtil.createMockImage());
        timeInput.SetHeight(HeightType.Stretch);
        timeInput.SetIsVisible(false);
        timeInput.SetMax("21:59");
        timeInput.SetMin("04:37");
        timeInput.SetPlaceholder("Sample placeholder");
        timeInput.SetSeparator(true);
        timeInput.SetSpacing(Spacing.Medium);
        timeInput.SetValue("18:00");

        Assert.assertEquals(timeInputNoDefaultValues, timeInput.Serialize());
    }

    @Test
    public void MaxTest() throws Exception
    {
        {
            final String inputTimeDefaultMax = "{\"id\":\"id\",\"type\":\"Input.Time\"}\n";

            TimeInput timeInput = TestUtil.createMockTimeInput();
            timeInput.SetMax("");
            Assert.assertEquals(inputTimeDefaultMax, timeInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTimeDefaultMax), "1.0");
            TimeInput parsedTimeInput = TestUtil.castToTimeInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedTimeInput.GetMax());
        }

        {
            final String inputNumberMaxTemplate =
                "{\"id\":\"id\",\"max\":\"%s\",\"type\":\"Input.Time\"}\n";
            String[] tests = {"00:23", "7:46", "03:43", "02:22", "10:36", "13:52", "14:08", "19:10"};

            for (int i = 0; i < tests.length; ++i)
            {
                String maxJson = String.format(inputNumberMaxTemplate, tests[i]);

                TimeInput timeInput = TestUtil.createMockTimeInput();
                timeInput.SetMax(tests[i]);
                Assert.assertEquals(maxJson, timeInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(maxJson), "1.0");
                TimeInput parsedTimeInput = TestUtil.castToTimeInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedTimeInput.GetMax());
            }
        }
    }

    @Test
    public void MinTest() throws Exception
    {
        {
            final String inputTimeDefaultMax = "{\"id\":\"id\",\"type\":\"Input.Time\"}\n";

            TimeInput timeInput = TestUtil.createMockTimeInput();
            timeInput.SetMin("");
            Assert.assertEquals(inputTimeDefaultMax, timeInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTimeDefaultMax), "1.0");
            TimeInput parsedTimeInput = TestUtil.castToTimeInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedTimeInput.GetMin());
        }

        {
            final String inputNumberMaxTemplate =
                "{\"id\":\"id\",\"min\":\"%s\",\"type\":\"Input.Time\"}\n";
            String[] tests = {"00:23", "7:46", "03:43", "02:22", "10:36", "13:52", "14:08", "19:10"};

            for (int i = 0; i < tests.length; ++i)
            {
                String maxJson = String.format(inputNumberMaxTemplate, tests[i]);

                TimeInput timeInput = TestUtil.createMockTimeInput();
                timeInput.SetMin(tests[i]);
                Assert.assertEquals(maxJson, timeInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(maxJson), "1.0");
                TimeInput parsedTimeInput = TestUtil.castToTimeInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedTimeInput.GetMin());
            }
        }
    }

    @Test
    public void PlaceholderTest() throws Exception
    {
        {
            final String inputTimeDefaultPlaceholder = "{\"id\":\"id\",\"type\":\"Input.Time\"}\n";

            TimeInput timeInput = TestUtil.createMockTimeInput();
            timeInput.SetPlaceholder("");
            Assert.assertEquals(inputTimeDefaultPlaceholder, timeInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTimeDefaultPlaceholder), "1.0");
            TimeInput parsedTimeInput = TestUtil.castToTimeInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedTimeInput.GetPlaceholder());
        }

        {
            final String inputTimePlaceholderTemplate = "{\"id\":\"id\",\"placeholder\":\"%s\",\"type\":\"Input.Time\"}\n";
            String tests[] = {"Sample text",
                "This is just a little bit tiny teeny bit larger than the one before this one a.k.a. index [0]",
                "The quick brown fox jumps over the lazy dog",
                "{{DATE(2017-02-14T06:08:39Z,LONG)}}",
                "This is some **bold** text"};

            for (int i = 0; i < tests.length; ++i)
            {
                String inputTimePlaceholderJson = String.format(inputTimePlaceholderTemplate, tests[i]);

                TimeInput timeInput = TestUtil.createMockTimeInput();
                timeInput.SetPlaceholder(tests[i]);
                Assert.assertEquals(inputTimePlaceholderJson, timeInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTimePlaceholderJson), "1.0");
                TimeInput parsedTimeInput = TestUtil.castToTimeInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedTimeInput.GetPlaceholder());
            }
        }
    }

    @Test
    public void ValueTest() throws Exception
    {
        {
            final String inputTimeDefaultPlaceholder = "{\"id\":\"id\",\"type\":\"Input.Time\"}\n";

            TimeInput timeInput = TestUtil.createMockTimeInput();
            timeInput.SetValue("");
            Assert.assertEquals(inputTimeDefaultPlaceholder, timeInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTimeDefaultPlaceholder), "1.0");
            TimeInput parsedTimeInput = TestUtil.castToTimeInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedTimeInput.GetValue());
        }

        {
            final String inputTimePlaceholderTemplate = "{\"id\":\"id\",\"type\":\"Input.Time\",\"value\":\"%s\"}\n";
            String tests[] = {"07:15", "15:14", "17:30", "18:40", "19:53"};

            for (int i = 0; i < tests.length; ++i)
            {
                String inputTimePlaceholderJson = String.format(inputTimePlaceholderTemplate, tests[i]);

                TimeInput timeInput = TestUtil.createMockTimeInput();
                timeInput.SetValue(tests[i]);
                Assert.assertEquals(inputTimePlaceholderJson, timeInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTimePlaceholderJson), "1.0");
                TimeInput parsedTimeInput = TestUtil.castToTimeInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedTimeInput.GetValue());
            }
        }
    }

    @Test
    public void TimeFormatting() throws Exception
    {
        ArrayList<Pair<Integer, Integer>> formatTestCases = new ArrayList<>();
        formatTestCases.add(new Pair<>(7, 15));
        formatTestCases.add(new Pair<>(11, 23));
        formatTestCases.add(new Pair<>(12, 0));
        formatTestCases.add(new Pair<>(15, 14));
        formatTestCases.add(new Pair<>(17, 30));
        formatTestCases.add(new Pair<>(21, 40));

        String formatTestResults[] = {"7:15 AM", "11:23 AM", "12:00 PM", "3:14 PM", "5:30 PM", "9:40 PM" };

        for (int i = 0; i < formatTestCases.size(); ++i)
        {
            Pair<Integer, Integer> formatTestCase = formatTestCases.get(i);

            Calendar calendar = new GregorianCalendar(0, 0, 0, formatTestCase.first, formatTestCase.second);
            String formattedValue = TimeInputRenderer.getTimeFormat().format(calendar.getTime());

            Assert.assertEquals(formatTestResults[i], formattedValue);


            Date value = TimeInputRenderer.getTimeFormat().parse(formatTestResults[i]);
            calendar = new GregorianCalendar();
            calendar.setTime(value);

            Assert.assertEquals((int)formatTestCase.first, calendar.get(Calendar.HOUR_OF_DAY));
            Assert.assertEquals((int)formatTestCase.second, calendar.get(Calendar.MINUTE));
        }

        /*
        String parsingTestCases[] = {};

        Date value = TimeInputRenderer.getTimeFormat().parse(m_editText.getText().toString());
        calendar = new GregorianCalendar();
        */

    }

}
