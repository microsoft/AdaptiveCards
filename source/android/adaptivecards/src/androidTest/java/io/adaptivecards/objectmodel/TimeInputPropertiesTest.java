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
            "{\"errorMessage\":\"Error message\"," +
                "\"id\":\"id\"," +
                "\"label\":\"Input label\"," +
                "\"max\":\"23:59\"," +
                "\"min\":\"00:00\"," +
                "\"placeholder\":\"Sample placeholder\"," +
                "\"type\":\"Input.Time\"," +
                "\"value\":\"16:20\"}\n";

        TimeInput timeInput = TestUtil.createMockTimeInput();
        timeInput.SetErrorMessage("Error message");
        timeInput.SetLabel("Input label");
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
            "{\"errorMessage\":\"Error message\"," +
                "\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                "\"height\":\"Stretch\"," +
                "\"id\":\"id\"," +
                "\"isVisible\":false," +
                "\"label\":\"Input label\"," +
                "\"max\":\"21:59\"," +
                "\"min\":\"04:37\"," +
                "\"placeholder\":\"Sample placeholder\"," +
                "\"separator\":true," +
                "\"spacing\":\"medium\"," +
                "\"type\":\"Input.Time\"," +
                "\"value\":\"18:00\"}\n";

        TimeInput timeInput = TestUtil.createMockTimeInput();
        timeInput.SetErrorMessage("Error message");
        timeInput.SetFallbackType(FallbackType.Content);
        timeInput.SetFallbackContent(TestUtil.createMockImage());
        timeInput.SetHeight(HeightType.Stretch);
        timeInput.SetIsVisible(false);
        timeInput.SetLabel("Input label");
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
        TimeInputCommand<String> c = new TimeInputCommand<String>() {
            @Override
            public String get(TimeInput element) { return element.GetMax(); }

            @Override
            public void set(String value, TimeInput element) { element.SetMax(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputTime, "");

        final String inputNumberMaxTemplate = "{\"id\":\"id\",\"max\":\"%s\",\"type\":\"Input.Time\"}\n";
        TestUtil.executeTests(c, inputNumberMaxTemplate, c_timeTestCases);
    }

    @Test
    public void MinTest() throws Exception
    {
        TimeInputCommand<String> c = new TimeInputCommand<String>() {
            @Override
            public String get(TimeInput element) { return element.GetMin(); }

            @Override
            public void set(String value, TimeInput element) { element.SetMin(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputTime, "");

        final String inputNumberMaxTemplate = "{\"id\":\"id\",\"min\":\"%s\",\"type\":\"Input.Time\"}\n";
        TestUtil.executeTests(c, inputNumberMaxTemplate, c_timeTestCases);
    }

    @Test
    public void PlaceholderTest() throws Exception
    {
        TimeInputCommand<String> c = new TimeInputCommand<String>() {
            @Override
            public String get(TimeInput element) { return element.GetPlaceholder(); }

            @Override
            public void set(String value, TimeInput element) { element.SetPlaceholder(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputTime, "");

        final String inputTimePlaceholderTemplate = "{\"id\":\"id\",\"placeholder\":\"%s\",\"type\":\"Input.Time\"}\n";
        TestUtil.executeTests(c, inputTimePlaceholderTemplate, TestUtil.c_regularStringTestCases);
        TestUtil.executeTests(c, inputTimePlaceholderTemplate, TestUtil.c_dateStringTestCases);
    }

    @Test
    public void ValueTest() throws Exception
    {
        TimeInputCommand<String> c = new TimeInputCommand<String>() {
            @Override
            public String get(TimeInput element) { return element.GetValue(); }

            @Override
            public void set(String value, TimeInput element) { element.SetValue(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputTime, "");

        final String inputTimePlaceholderTemplate = "{\"id\":\"id\",\"type\":\"Input.Time\",\"value\":\"%s\"}\n";
        TestUtil.executeTests(c, inputTimePlaceholderTemplate, c_timeTestCases);
    }

    @Test
    public void LabelTest() throws Exception
    {
        TimeInputCommand<String> c = new TimeInputCommand<String>() {
            @Override
            public String get(TimeInput element) { return element.GetLabel(); }

            @Override
            public void set(String value, TimeInput element) { element.SetLabel(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputTime, "");

        final String inputTextLabelTemplate = "{\"id\":\"id\",\"label\":\"%s\",\"type\":\"Input.Time\"}\n";
        TestUtil.executeTests(c, inputTextLabelTemplate, TestUtil.c_regularStringTestCases);
    }

    @Test
    public void ErrorMessageTest() throws Exception
    {
        TimeInputCommand<String> c = new TimeInputCommand<String>() {
            @Override
            public String get(TimeInput element) { return element.GetErrorMessage(); }

            @Override
            public void set(String value, TimeInput element) { element.SetErrorMessage(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputTime, "");

        final String inputTextErrorMessageTemplate = "{\"errorMessage\":\"%s\",\"id\":\"id\",\"type\":\"Input.Time\"}\n";
        TestUtil.executeTests(c, inputTextErrorMessageTemplate, TestUtil.c_regularStringTestCases);
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
    }

    private abstract class TimeInputCommand<E> implements TestUtil.Command<TimeInput, E>
    {
        @Override
        public TimeInput getMockObject()
        {
            return TestUtil.createMockTimeInput();
        }

        @Override
        public TimeInput castTo(BaseCardElement element) {
            return TestUtil.castToTimeInput(element);
        }
    }

    private final String c_defaultInputTime = "{\"id\":\"id\",\"type\":\"Input.Time\"}\n";

    private final String c_timeTestCases[] = {"07:15", "15:14", "17:30", "18:40", "19:53", "00:23", "7:46", "03:43", "02:22", "10:36", "13:52", "14:08", "19:10"};

}
