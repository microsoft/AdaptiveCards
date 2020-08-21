package io.adaptivecards.objectmodel;

import android.support.test.InstrumentationRegistry;
import android.support.v4.app.FragmentManager;
import android.util.Pair;
import android.widget.EditText;

import junit.framework.Assert;

import org.junit.Test;

import java.sql.Time;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

import io.adaptivecards.renderer.input.TimeInputRenderer;
import io.adaptivecards.renderer.inputhandler.BaseInputHandler;
import io.adaptivecards.renderer.inputhandler.DateInputHandler;
import io.adaptivecards.renderer.inputhandler.NumberInputHandler;
import io.adaptivecards.renderer.inputhandler.TimeInputHandler;
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

    /**
     * isRequiredValidation
     * This method only checks if the isRequired property is being checked correctly
     * If there is no value in the input it should fail
     * Any value, as long as it can be casted into a time with our format, should succeed
     */
    @Test
    public void isRequiredValidation()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", "", true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);

        // Validate that empty input is always invalid
        Assert.assertEquals(false, timeInputHandler.isValid());

        // Validate required
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallTimeValues, c_inRangeTimeValues, c_largeTimeValues), true, validationExecutor);
    }

    /**
     * isRequiredForInvalidValuesValidation
     * This method only checks if the isRequired property is being checked correctly when an invalid
     * value is provided
     * If there is a value, but it can't be casted into a time with our format, it should fail
     */
    @Test
    public void isRequiredForInvalidValuesValidation()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", "", true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);

        // Validate that empty input is always invalid
        Assert.assertEquals(false, timeInputHandler.isValid());

        // Invalid dates should not succeed as required
        TestUtil.runValidationTests(c_invalidTimeValues, false, validationExecutor);
    }

    /**
     * isRequiredOnlyTest
     * This method only verifies that the isValid method verifies correctly that any input value,
     * even if not valid, will return true.
     */
    @Test
    public void isRequiredOnlyTest()
    {
        TimeInput timeInput = TestUtil.createMockTimeInput();
        timeInput.SetIsRequired(true);

        // Create a custom number input handler that ignores any type of check
        class CustomTimeInputHandler extends TimeInputHandler
        {
            public CustomTimeInputHandler(BaseInputElement baseInputElement, FragmentManager fragmentManager) { super(baseInputElement, fragmentManager); }

            @Override
            public boolean isValidOnSpecifics(String timeInputValue) { return true; }
        }

        TimeInputHandler timeInputHandler = new CustomTimeInputHandler(timeInput, null);
        timeInputHandler.setView(new EditText(InstrumentationRegistry.getContext()));

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);

        // Validate that empty input is always invalid
        Assert.assertEquals(false, timeInputHandler.isValid());

        // Any input should succeed
        TestUtil.runValidationTests(c_invalidTimeValues, true, validationExecutor);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallTimeValues, c_inRangeTimeValues, c_largeTimeValues), true, validationExecutor);
    }

    /**
     * SpecificMinValidationForNonRequiredAndEmptyInputTest
     * This test verifies the behaviour of the isValidOnSpecifics method when a min value has been set
     * As the input is not required, an empty value should succeed
     */
    @Test
    public void SpecificMinValidationForNonRequiredAndEmptyInputTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(c_inRangeTimeValues[0], "");
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate that empty input is always valid when not required
        Assert.assertEquals(true, timeInputHandler.isValidOnSpecifics(""));
    }

    /**
     * SpecificMinValidationForNonRequiredInputTest
     * This test verifies the behaviour of the isValidOnSpecifics method when a min value has been set
     * When the input is not empty, any value smaller than the min should fail
     */
    @Test
    public void SpecificMinValidationForNonRequiredInputTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(c_inRangeTimeValues[0], "");
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate only min
        TestUtil.SpecificsValidationExecutor minValidationExecutor = new TestUtil.SpecificsValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_smallTimeValues, false, minValidationExecutor);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_inRangeTimeValues, c_largeTimeValues), true, minValidationExecutor);
    }

    /**
     * SpecificMinValidationForNonRequiredAndInvalidInputTest
     * This test verifies the behaviour of the isValidOnSpecifics method when a min value has been set
     * When the input has a value that can't be parsed into a time, it should fail
     */
    @Test
    public void SpecificMinValidationForNonRequiredAndInvalidInputTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(c_inRangeTimeValues[0], "");
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Invalid time values for non required inputs are considered invalid
        TestUtil.SpecificsValidationExecutor minValidationExecutor = new TestUtil.SpecificsValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, minValidationExecutor);
    }

    /**
     * ValidationForNonRequiredAndEmptyInputWithMinValueTest
     * This test verifies the behaviour of the isValid method when a min value has been set
     * As the input is not required, an empty value should succeed
     */
    @Test
    public void ValidationForNonRequiredAndEmptyInputWithMinValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(c_inRangeTimeValues[0], "");
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate that empty input is always valid
        Assert.assertEquals(true, timeInputHandler.isValid());
    }

    /**
     * ValidationForNonRequiredInputWithMinValueTest
     * This test verifies the behaviour of the isValid method when a min value has been set
     * When the input is not empty, any value smaller than the min should fail
     */
    @Test
    public void ValidationForNonRequiredInputWithMinValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(c_inRangeTimeValues[0], "");
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate non-required + min
        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_smallTimeValues, false, validationExecutor);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_inRangeTimeValues, c_largeTimeValues), true, validationExecutor);
    }

    /**
     * ValidationForNonRequiredAndInvalidInputWithMinValueTest
     * This test verifies the behaviour of the isValid method when a min value has been set
     * When the input has a value that can't be parsed into a time, it should fail
     */
    @Test
    public void ValidationForNonRequiredAndInvalidInputWithMinValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(c_inRangeTimeValues[0], "");
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Invalid time values for non required inputs are considered invalid
        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, validationExecutor);
    }

    /**
     * ValidationForRequiredAndEmptyInputWithMinValueTest
     * This test verifies the behaviour of the isValid method when a min value has been set
     * As the input is required, an empty value should fail
     */
    @Test
    public void ValidationForRequiredAndEmptyInputWithMinValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(c_inRangeTimeValues[0], "", true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate that empty input is invalid
        Assert.assertEquals(false, timeInputHandler.isValid());
    }

    /**
     * ValidationForRequiredInputWithMinValueTest
     * This test verifies the behaviour of the isValid method when a min value has been set
     * When the input is not empty, any value smaller than the min should fail
     */
    @Test
    public void ValidationForRequiredInputWithMinValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(c_inRangeTimeValues[0], "", true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate non-required + min
        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_smallTimeValues, false, validationExecutor);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_inRangeTimeValues, c_largeTimeValues), true, validationExecutor);
    }

    /**
     * ValidationForRequiredAndInvalidInputWithMinValueTest
     * This test verifies the behaviour of the isValid method when a min value has been set
     * When the input has a value that can't be parsed into a time, it should fail
     */
    @Test
    public void ValidationForRequiredAndInvalidInputWithMinValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(c_inRangeTimeValues[0], "", true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Invalid time values for non required inputs are considered invalid
        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, validationExecutor);
    }

    /**
     * SpecificMaxValidationForNonRequiredAndEmptyInputTest
     * This test verifies the behaviour of the isValidOnSpecifics method when a max value has been set
     * As the input is not required, an empty value should succeed
     */
    @Test
    public void SpecificMaxValidationForNonRequiredAndEmptyInputTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", c_inRangeTimeValues[c_inRangeTimeValues.length - 1]);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate that empty input is always valid
        Assert.assertEquals(true, timeInputHandler.isValidOnSpecifics(""));
    }

    /**
     * SpecificMaxValidationForNonRequiredInputTest
     * This test verifies the behaviour of the isValidOnSpecifics method when a max value has been set
     * When the input is not empty, any value larger than the max should fail
     */
    @Test
    public void SpecificMaxValidationForNonRequiredInputTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", c_inRangeTimeValues[c_inRangeTimeValues.length - 1]);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate only max
        TestUtil.SpecificsValidationExecutor maxValidationExecutor = new TestUtil.SpecificsValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallTimeValues, c_inRangeTimeValues), true, maxValidationExecutor);
        TestUtil.runValidationTests(c_largeTimeValues, false, maxValidationExecutor);
    }

    /**
     * SpecificMaxValidationForNonRequiredAndInvalidInputTest
     * This test verifies the behaviour of the isValidOnSpecifics method when a max value has been set
     * When the input has a value that can't be parsed into a time, it should fail
     */
    @Test
    public void SpecificMaxValidationForNonRequiredAndInvalidInputTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", c_inRangeTimeValues[c_inRangeTimeValues.length - 1]);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Invalid time values for non required inputs are considered invalid
        TestUtil.SpecificsValidationExecutor maxValidationExecutor = new TestUtil.SpecificsValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, maxValidationExecutor);
    }

    /**
     * ValidationForNonRequiredAndEmptyInputWithMaxValueTest
     * This test verifies the behaviour of the isValid method when a max value has been set
     * As the input is not required, an empty value should succeed
     */
    @Test
    public void ValidationForNonRequiredAndEmptyInputWithMaxValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", c_inRangeTimeValues[c_inRangeTimeValues.length - 1]);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate that empty input is always valid
        Assert.assertEquals(true, timeInputHandler.isValid());
    }

    /**
     * ValidationForNonRequiredInputWithMaxValueTest
     * This test verifies the behaviour of the isValid method when a max value has been set
     * When the input is not empty, any value larger than the max should fail
     */
    @Test
    public void ValidationForNonRequiredInputWithMaxValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", c_inRangeTimeValues[c_inRangeTimeValues.length - 1]);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate non-required + max
        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallTimeValues, c_inRangeTimeValues), true, validationExecutor);
        TestUtil.runValidationTests(c_largeTimeValues, false, validationExecutor);
    }

    /**
     * ValidationForNonRequiredAndInvalidInputWithMaxValueTest
     * This test verifies the behaviour of the isValid method when a max value has been set
     * When the input has a value that can't be parsed into a time, it should fail
     */
    @Test
    public void ValidationForNonRequiredAndInvalidInputWithMaxValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", c_inRangeTimeValues[c_inRangeTimeValues.length - 1]);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Invalid time values for non required inputs are considered invalid
        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, validationExecutor);
    }

    /**
     * ValidationForRequiredAndEmptyInputWithMaxValueTest
     * This test verifies the behaviour of the isValid method when a max value has been set
     * As the input is required, an empty value should fail
     */
    @Test
    public void ValidationForRequiredAndEmptyInputWithMaxValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", c_inRangeTimeValues[c_inRangeTimeValues.length - 1], true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate that empty input is invalid
        Assert.assertEquals(false, timeInputHandler.isValid());
    }

    /**
     * ValidationForRequiredInputWithMaxValueTest
     * This test verifies the behaviour of the isValid method when a max value has been set
     * When the input is not empty, any value larger than the max should fail
     */
    @Test
    public void ValidationForRequiredInputWithMaxValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", c_inRangeTimeValues[c_inRangeTimeValues.length - 1], true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate non-required + max
        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallTimeValues, c_inRangeTimeValues), true, validationExecutor);
        TestUtil.runValidationTests(c_largeTimeValues, false, validationExecutor);
    }

    /**
     * ValidationForRequiredAndInvalidInputWithMaxValueTest
     * This test verifies the behaviour of the isValid method when a max value has been set
     * When the input has a value that can't be parsed into a time, it should fail
     */
    @Test
    public void ValidationForRequiredAndInvalidInputWithMaxValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", c_inRangeTimeValues[c_inRangeTimeValues.length - 1], true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Invalid time values for non required inputs are considered invalid
        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, validationExecutor);
    }

    /**
     * SpecificMinMaxValidationForNonRequiredAndEmptyInputTest
     * This test verifies the behaviour of the isValidOnSpecifics method when a min and max values have been set
     * As the input is not required, an empty value should succeed
     */
    @Test
    public void SpecificMinMaxValidationForNonRequiredAndEmptyInputTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(c_inRangeTimeValues[0], c_inRangeTimeValues[c_inRangeTimeValues.length - 1]);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate that empty input is always valid
        Assert.assertEquals(true, timeInputHandler.isValidOnSpecifics(""));
    }

    /**
     * SpecificMinMaxValidationForNonRequiredInputTest
     * This test verifies the behaviour of the isValidOnSpecifics method when a min and max values have been set
     * When the input is not empty, any value smaller than the min should fail
     * When the input is not empty, any value larger than the max should fail
     */
    @Test
    public void SpecificMinMaxValidationForNonRequiredInputTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("08:27", "17:42");
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate min + max
        TestUtil.SpecificsValidationExecutor minMaxValidationExecutor = new TestUtil.SpecificsValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_smallTimeValues, false, minMaxValidationExecutor);
        TestUtil.runValidationTests(c_inRangeTimeValues, true, minMaxValidationExecutor);
        TestUtil.runValidationTests(c_largeTimeValues, false, minMaxValidationExecutor);
    }

    /**
     * SpecificMinMaxValidationForNonRequiredAndInvalidInputTest
     * This test verifies the behaviour of the isValidOnSpecifics method when a min and max values have been set
     * When the input has a value that can't be parsed into a time, it should fail
     */
    @Test
    public void SpecificMinMaxValidationForNonRequiredAndInvalidInputTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(c_inRangeTimeValues[0], c_inRangeTimeValues[c_inRangeTimeValues.length - 1]);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Invalid time values for non required inputs are considered invalid
        TestUtil.SpecificsValidationExecutor minMaxValidationExecutor = new TestUtil.SpecificsValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, minMaxValidationExecutor);
    }

    /**
     * ValidationForNonRequiredInputWithMinMaxValueTest
     * This test verifies the behaviour of the isValid method when a min and max value have been set
     * As the input is not required, an empty value should succeed
     */
    @Test
    public void ValidationForNonRequiredAndEmptyInputWithMinMaxValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(c_inRangeTimeValues[0], c_inRangeTimeValues[c_inRangeTimeValues.length - 1]);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate that empty input is always valid
        Assert.assertEquals(true, timeInputHandler.isValid());
    }

    /**
     * ValidationForNonRequiredInputWithMinMaxValueTest
     * This test verifies the behaviour of the isValid method when a min and max value have been set
     * When the input is not empty, any value smaller than the min should fail
     * When the input is not empty, any value larger than the max should fail
     */
    @Test
    public void ValidationForNonRequiredInputWithMinMaxValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(c_inRangeTimeValues[0], c_inRangeTimeValues[c_inRangeTimeValues.length - 1]);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate min + max + non-required
        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_smallTimeValues, false, validationExecutor);
        TestUtil.runValidationTests(c_inRangeTimeValues, true, validationExecutor);
        TestUtil.runValidationTests(c_largeTimeValues, false, validationExecutor);
    }

    /**
     * ValidationForNonRequiredAndInvalidInputWithMinMaxValueTest
     * This test verifies the behaviour of the isValid method when a min and max value have been set
     * When the input has a value that can't be parsed into a time, it should fail
     */
    @Test
    public void ValidationForNonRequiredAndInvalidInputWithMinMaxValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(c_inRangeTimeValues[0], c_inRangeTimeValues[c_inRangeTimeValues.length - 1]);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Invalid time values for non required inputs are considered invalid
        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, validationExecutor);
    }

    /**
     * ValidationForNonRequiredInputWithMinMaxValueTest
     * This test verifies the behaviour of the isValid method when a min and max value have been set
     * As the input is required, an empty value should fail
     */
    @Test
    public void ValidationForRequiredAndEmptyInputWithMinMaxValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(c_inRangeTimeValues[0], c_inRangeTimeValues[c_inRangeTimeValues.length - 1], true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate that empty input is invalid
        Assert.assertFalse(timeInputHandler.isValid());
    }

    /**
     * ValidationForNonRequiredInputWithMinMaxValueTest
     * This test verifies the behaviour of the isValid method when a min and max value have been set
     * When the input is not empty, any value smaller than the min should fail
     * When the input is not empty, any value larger than the max should fail
     */
    @Test
    public void ValidationForRequiredInputWithMinMaxValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(c_inRangeTimeValues[0], c_inRangeTimeValues[c_inRangeTimeValues.length - 1], true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Validate min + max + non-required
        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_smallTimeValues, false, validationExecutor);
        TestUtil.runValidationTests(c_inRangeTimeValues, true, validationExecutor);
        TestUtil.runValidationTests(c_largeTimeValues, false, validationExecutor);
    }

    /**
     * ValidationForNonRequiredInputWithMinMaxValueTest
     * This test verifies the behaviour of the isValid method when a min and max value have been set
     * When the input has a value that can't be parsed into a time, it should fail
     */
    @Test
    public void ValidationForRequiredAndInvalidInputWithMinMaxValueTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(c_inRangeTimeValues[0], c_inRangeTimeValues[c_inRangeTimeValues.length - 1], true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Invalid number values for non required inputs are considered invalid
        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, validationExecutor);
    }

    private TimeInput createTimeInputWithValidationProperties(String minTime, String maxTime)
    {
        return createTimeInputWithValidationProperties(minTime, maxTime, false);
    }

    private TimeInput createTimeInputWithValidationProperties(String minTime, String maxTime, boolean isRequired)
    {
        TimeInput timeInput = TestUtil.createMockTimeInput();
        timeInput.SetMin(minTime);
        timeInput.SetMax(maxTime);
        timeInput.SetIsRequired(isRequired);
        return timeInput;
    }

    private TimeInputHandler createInputHandler(TimeInput timeInput)
    {
        TimeInputHandler timeInputHandler = new TimeInputHandler(timeInput, null);
        timeInputHandler.setView(new EditText(InstrumentationRegistry.getContext()));
        return timeInputHandler;
    }

    private final String[] c_smallTimeValues = {"12:00 AM", "02:12 AM", "04:17 AM", "05:33 AM", "06:53 AM", "07:04 AM", "08:26 AM"};
    private final String[] c_inRangeTimeValues = {"08:27 AM", "09:35 AM", "10:08 AM", "01:47 PM", "02:50 PM", "04:16 PM", "05:42 PM"};
    private final String[] c_largeTimeValues = {"05:43 PM", "07:56 PM", "08:11 PM", "09:42 PM", "10:51 PM", "11:21 PM", "11:59 PM"};
    private final String[] c_invalidTimeValues = {"aWord", "1:1", "2:3:432:5:6", "12-12-2012", ":", "12_23"};

    private final String c_defaultInputTime = "{\"id\":\"id\",\"type\":\"Input.Time\"}\n";

    private final String c_timeTestCases[] = {"07:15", "15:14", "17:30", "18:40", "19:53", "00:23", "7:46", "03:43", "02:22", "10:36", "13:52", "14:08", "19:10"};

}
