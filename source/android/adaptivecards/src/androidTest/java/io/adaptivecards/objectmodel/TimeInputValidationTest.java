package io.adaptivecards.objectmodel;

import android.support.test.InstrumentationRegistry;
import android.support.v4.app.FragmentManager;
import android.widget.EditText;

import junit.framework.Assert;

import org.junit.Test;
import org.junit.runner.Description;

import io.adaptivecards.renderer.inputhandler.TimeInputHandler;

public class TimeInputValidationTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    private TimeInput createTimeInputWithValidationProperties(String minTime, String maxTime)
    {
        return createTimeInputWithValidationProperties(minTime, maxTime, false);
    }

    private TimeInput createTimeInputWithValidationProperties(String minTime, String maxTime, boolean isRequired)
    {
        TimeInput dateInput = TestUtil.createMockTimeInput();
        dateInput.SetMin(minTime);
        dateInput.SetMax(maxTime);
        dateInput.SetIsRequired(isRequired);
        return dateInput;
    }

    private TimeInputHandler createInputHandler(TimeInput dateInput)
    {
        TimeInputHandler dateInputHandler = new TimeInputHandler(dateInput, null);
        dateInputHandler.setView(new EditText(InstrumentationRegistry.getContext()));
        return dateInputHandler;
    }

    private TimeInputHandler createCustomInputHandlerWithoutSpecificValidation(TimeInput dateInput)
    {
        class CustomTimeInputHandler extends TimeInputHandler
        {
            public CustomTimeInputHandler(BaseInputElement baseInputElement, FragmentManager fragmentManager) { super(baseInputElement, fragmentManager); }

            @Override
            public boolean isValidOnSpecifics(String dateInputValue) { return true; }
        }

        TimeInputHandler dateInputHandler = new CustomTimeInputHandler(dateInput, null);
        dateInputHandler.setView(new EditText(InstrumentationRegistry.getContext()));

        return dateInputHandler;
    }

    private final String smallestInRangeValue = "08:27";
    private final String largestInRangeValue = "17:42";

    private final String[] c_smallTimeValues = {"12:00 AM", "02:12 AM", "04:17 AM", "05:33 AM", "06:53 AM", "07:04 AM", "08:26 AM"};
    private final String[] c_inRangeTimeValues = {"08:27 AM", "09:35 AM", "10:08 AM", "01:47 PM", "02:50 PM", "04:16 PM", "05:42 PM"};
    private final String[] c_largeTimeValues = {"05:43 PM", "07:56 PM", "08:11 PM", "09:42 PM", "10:51 PM", "11:21 PM", "11:59 PM"};
    private final String[] c_invalidTimeValues = {"aWord", "1:1", "2:3:432:5:6", "12-12-2012", ":", "12_23"};

    /**
     * VerifyIsRequiredValidationFailsWithNoSetValue
     * @testDescription Verifies that an input with isRequired = true will fail when no value has been set
     */
    @Test
    public void VerifyIsRequiredValidationFailsWithNoSetValue()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", "", true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        Assert.assertFalse(timeInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationSucceedsWithSetValue
     * @testDescription Verifies that an input with isRequired = true will succeed when a valid time has been set
     */
    @Test
    public void VerifyIsRequiredValidationSucceedsWithSetValue()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", "", true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallTimeValues, c_inRangeTimeValues, c_largeTimeValues), true, validationExecutor);
    }

    /**
     * VerifyIsRequiredValidationFailsWithSetInvalidValue
     * @testDescription Verifies that an input with isRequired = true will fail when an invalid time has been set
     */
    @Test
    public void VerifyIsRequiredValidationFailsWithSetInvalidValue()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", "", true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, validationExecutor);
    }

    /**
     * VerifyOnlyIsRequiredValidationFailsWithNoSetValue
     * @testDescription Verifies that the isRequired check shared by all InputValidation classes fails when no value has been set
     */
    @Test
    public void VerifyOnlyIsRequiredValidationFailsWithNoSetValue()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", "", true);
        TimeInputHandler timeInputHandler = createCustomInputHandlerWithoutSpecificValidation(timeInput);

        Assert.assertFalse(timeInputHandler.isValid());
    }

    /**
     * VerifyOnlyIsRequiredValidationSucceedsWithSetValidValue
     * @testDescription Verifies that the isRequired check shared by all InputValidation classes fails when a valid time has been set
     */
    @Test
    public void VerifyOnlyIsRequiredValidationSucceedsWithSetValidValue()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", "", true);
        TimeInputHandler timeInputHandler = createCustomInputHandlerWithoutSpecificValidation(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallTimeValues, c_inRangeTimeValues, c_largeTimeValues), true, validationExecutor);
    }

    /**
     * VerifyOnlyIsRequiredValidationSucceedsWithSetInvalidValue
     * @testDescription Verifies that the isRequired check shared by all InputValidation classes fails when an invalid time has been set
     */
    @Test
    public void VerifyOnlyIsRequiredValidationSucceedsWithSetInvalidValue()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", "", true);
        TimeInputHandler timeInputHandler = createCustomInputHandlerWithoutSpecificValidation(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, true, validationExecutor);
    }

    /**
     * VerifySpecificMinValidationSucceedsWithNoSetValue
     * @testDescription Verifies that the min validation (isValidOnSpecifics) succeeds when no time
     * has been set and it's not required as there's no comparison to be made
     */
    @Test
    public void VerifySpecificMinValidationSucceedsWithNoSetValue()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, "");
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        Assert.assertTrue(timeInputHandler.isValidOnSpecifics(""));
    }

    /**
     * VerifySpecificMinValidationFailsWithSmallValues
     * @testDescription Verifies that the min validation (isValidOnSpecifics) fails when a prior time to the min time has been set
     */
    @Test
    public void VerifySpecificMinValidationFailsWithSmallValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, "");
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.SpecificsValidationExecutor minValidationExecutor = new TestUtil.SpecificsValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_smallTimeValues, false, minValidationExecutor);
    }

    /**
     * VerifySpecificMinValidationSucceedsWithInRangeAndLargeValues
     * @testDescription Verifies that the min validation (isValidOnSpecifics) succeeds when the same or later time to the min time has been set
     */
    @Test
    public void VerifySpecificMinValidationSucceedsWithInRangeAndLargeValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, "");
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.SpecificsValidationExecutor minValidationExecutor = new TestUtil.SpecificsValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_inRangeTimeValues, c_largeTimeValues), true, minValidationExecutor);
    }

    /**
     * VerifySpecificMinValidationFailsWithInvalidValues
     * @testDescription Verifies that the min validation (isValidOnSpecifics) fails when an invalid time has been set
     */
    @Test
    public void VerifySpecificMinValidationFailsWithInvalidValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, "");
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.SpecificsValidationExecutor minValidationExecutor = new TestUtil.SpecificsValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, minValidationExecutor);
    }

    /**
     * VerifyMinValidationSucceedsWithNoSetValue
     * @testDescription  Verifies that the min validation (isValid) succeeds when no time has been set
     * and it's not required as there's no comparison to be made
     */
    @Test
    public void VerifyMinValidationSucceedsWithNoSetValue()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, "");
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        Assert.assertEquals(true, timeInputHandler.isValid());
    }

    /**
     * VerifyMinValidationFailsWithSmallValues
     *  @testDescription Verifies that the min validation (isValid) fails when a prior time to the min time has been set
     */
    @Test
    public void VerifyMinValidationFailsWithSmallValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, "");
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_smallTimeValues, false, validationExecutor);
    }

    /**
     * VerifyMinValidationSucceedsWithInRangeAndLargeValues
     * @testDescription Verifies that the min validation (isValid) succeeds when the same or later time to the min time has been set
     */
    @Test
    public void VerifyMinValidationSucceedsWithInRangeAndLargeValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, "");
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_inRangeTimeValues, c_largeTimeValues), true, validationExecutor);
    }

    /**
     * VerifyMinValidationFailsWithInvalidValues
     * @testDescription Verifies that the min validation (isValid) fails when an invalid time has been set
     */
    @Test
    public void VerifyMinValidationFailsWithInvalidValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, "");
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMinValidationFailsWithNoSetValue
     * @testDescription Verifies that the min and isRequired validation (isValid) fails when no time has been set
     */
    @Test
    public void VerifyRequiredMinValidationFailsWithNoSetValue()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, "", true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        Assert.assertFalse(timeInputHandler.isValid());
    }

    /**
     * VerifyRequiredMinValidationFailsWithSmallValues
     * @testDescription Verifies that the min and isRequired validation (isValid) fails when a prior time to the min time has been set
     */
    @Test
    public void VerifyRequiredMinValidationFailsWithSmallValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, "", true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_smallTimeValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMinValidationSucceedsWithInRangeAndLargeValues
     * @testDescription Verifies that the min and isRequired validation (isValid) succeeds when the same or later time to the min time has been set
     */
    @Test
    public void VerifyRequiredMinValidationSucceedsWithInRangeAndLargeValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, "", true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_inRangeTimeValues, c_largeTimeValues), true, validationExecutor);
    }

    /**
     * VerifyRequiredMinValidationSucceedsWithInvalidValues
     * @testDescription Verifies that the min and isRequired validation (isValid) fails when an invalid time has been set
     */
    @Test
    public void VerifyRequiredMinValidationSucceedsWithInvalidValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, "", true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        // Invalid time values for non required inputs are considered invalid
        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, validationExecutor);
    }

    /**
     * VerifySpecificMaxValidationSucceedsWithNoSetValue
     * @testDescription Verifies that the max validation (isValidOnSpecifics) succeeds when no time has been set
     */
    @Test
    public void VerifySpecificMaxValidationSucceedsWithNoSetValue()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        Assert.assertTrue(timeInputHandler.isValidOnSpecifics(""));
    }

    /**
     * VerifySpecificMaxValidationSucceedsWithSmallAndInRangeValues
     * @testDescription Verifies that the max validation (isValidOnSpecifics) succeeds when same
     * or prior time to the max time has been set
     */
    @Test
    public void VerifySpecificMaxValidationSucceedsWithSmallAndInRangeValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.SpecificsValidationExecutor maxValidationExecutor = new TestUtil.SpecificsValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallTimeValues, c_inRangeTimeValues), true, maxValidationExecutor);
    }

    /**
     * VerifySpecificMaxValidationFailsWithLargeValues
     * @testDescription Verifies that the max validation (isValidOnSpecifics) fails when a later time to the max time has been set
     */
    @Test
    public void VerifySpecificMaxValidationFailsWithLargeValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.SpecificsValidationExecutor maxValidationExecutor = new TestUtil.SpecificsValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_largeTimeValues, false, maxValidationExecutor);
    }

    /**
     * VerifySpecificMaxValidationFailsWithInvalidValues
     * @testDescription Verifies that the max validation (isValidOnSpecifics) fails when an invalid time has been set
     */
    @Test
    public void VerifySpecificMaxValidationFailsWithInvalidValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.SpecificsValidationExecutor maxValidationExecutor = new TestUtil.SpecificsValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, maxValidationExecutor);
    }

    /**
     * VerifyMaxValidationSucceedsWithNoSetValue
     * @testDescription  Verifies that the max validation (isValid) succeeds when no time has been set
     * and it's not required as there's no comparison to be made
     */
    @Test
    public void VerifyMaxValidationSucceedsWithNoSetValue()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        Assert.assertTrue(timeInputHandler.isValid());
    }

    /**
     * VerifyMaxValidationSucceedsWithSmallAndInRangeValues
     * @testDescription Verifies that the max validation (isValid) succeeds when the same or a prior time to the max time has been set
     */
    @Test
    public void VerifyMaxValidationSucceedsWithSmallAndInRangeValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallTimeValues, c_inRangeTimeValues), true, validationExecutor);
    }

    /**
     * VerifyMaxValidationSucceedsWithLargeValues
     * @testDescription Verifies that the max validation (isValid) fails when a later time to the max time has been set
     */
    @Test
    public void VerifyMaxValidationSucceedsWithLargeValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_largeTimeValues, false, validationExecutor);
    }

    /**
     * VerifyMaxValidationFailsWithInvalidValues
     * @testDescription Verifies that the max validation (isValid) fails when an invalid time has been set
     */
    @Test
    public void VerifyMaxValidationFailsWithInvalidValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMaxValidationFailsWithNoSetValue
     * @testDescription  Verifies that the max and isRequired validation (isValid) fails when no time has been set
     */
    @Test
    public void VerifyRequiredMaxValidationFailsWithNoSetValue()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", largestInRangeValue, true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        Assert.assertFalse(timeInputHandler.isValid());
    }

    /**
     * VerifyRequiredMaxValidationSucceedsWithSmallAndInRangeValues
     * @testDescription  Verifies that the max and isRequired validation (isValid) succeeds when the same
     * or a prior time to the max time has been set
     */
    @Test
    public void VerifyRequiredMaxValidationSucceedsWithSmallAndInRangeValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", largestInRangeValue, true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallTimeValues, c_inRangeTimeValues), true, validationExecutor);
    }

    /**
     * VerifyRequiredMaxValidationFailsWithLargeValues
     * @testDescription  Verifies that the max and isRequired validation (isValid) fail when a later time to the max time has been set
     */
    @Test
    public void VerifyRequiredMaxValidationFailsWithLargeValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", largestInRangeValue, true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_largeTimeValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMaxValidationFailsWithInvalidValues
     * @testDescription  Verifies that the max and isRequired validation (isValid) fail when an invalid time has been set
     */
    @Test
    public void VerifyRequiredMaxValidationFailsWithInvalidValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties("", largestInRangeValue, true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, validationExecutor);
    }

    /**
     * VerifySpecificMinMaxValidationSucceedsWithNoSetValue
     * @testDescription Verifies that the min and max validation (isValidOnSpecifics) succeeds when no time has been set
     */
    @Test
    public void SpecificMinMaxValidationForNonRequiredAndEmptyInputTest()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        Assert.assertTrue(timeInputHandler.isValidOnSpecifics(""));
    }

    /**
     * VerifySpecificMinMaxValidationFailsWithSmallValues
     * @testDescription Verifies that the min and max validation (isValidOnSpecifics) fails when a prior time to the min time has been set
     */
    @Test
    public void VerifySpecificMinMaxValidationFailsWithSmallValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.SpecificsValidationExecutor minMaxValidationExecutor = new TestUtil.SpecificsValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_smallTimeValues, false, minMaxValidationExecutor);
    }

    /**
     * VerifySpecificMinMaxValidationSucceedsWithInRangeValues
     * @testDescription Verifies that the min and max validation (isValidOnSpecifics) succeeds when a
     * time has been set and it is the same or a later time to the min time and is the same or a prior
     * time to the max time
     */
    @Test
    public void VerifySpecificMinMaxValidationSucceedsWithInRangeValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.SpecificsValidationExecutor minMaxValidationExecutor = new TestUtil.SpecificsValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_inRangeTimeValues, true, minMaxValidationExecutor);
    }

    /**
     * VerifySpecificMinMaxValidationFailsWithLargeValues
     * @testDescription Verifies that the min and max validation (isValidOnSpecifics) fails when a later time to the max time has been set
     */
    @Test
    public void VerifySpecificMinMaxValidationFailsWithLargeValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.SpecificsValidationExecutor minMaxValidationExecutor = new TestUtil.SpecificsValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_largeTimeValues, false, minMaxValidationExecutor);
    }

    /**
     * VerifySpecificMinMaxValidationFailsWithInvalidValues
     * @testDescription Verifies that the min and max validation (isValidOnSpecifics) fails when an invalid time has been set
     */
    @Test
    public void VerifySpecificMinMaxValidationFailsWithInvalidValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.SpecificsValidationExecutor minMaxValidationExecutor = new TestUtil.SpecificsValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, minMaxValidationExecutor);
    }

    /**
     * VerifyMinMaxValidationFailsWithNoSetValue
     * @testDescription Verifies that the min and max validation (isValid) succeeds when no time has been set
     */
    @Test
    public void VerifyMinMaxValidationSucceedsWithNoSetValue()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        Assert.assertTrue(timeInputHandler.isValid());
    }

    /**
     * VerifyMinMaxValidationFailsWithSmallValues
     * @testDescription Verifies that the min and max validation (isValid) fails when a prior time to the min time has been set
     */
    @Test
    public void VerifyMinMaxValidationFailsWithSmallValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_smallTimeValues, false, validationExecutor);
    }

    /**
     * VerifyMinMaxValidationSucceedsWithInRangeValues
     * @testDescription Verifies that the min and max validation (isValid) succeeds when a time has been set and
     * it is the same or a later time to the min time and is the same or a prior time to the max time
     */
    @Test
    public void VerifyMinMaxValidationSucceedsWithInRangeValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_inRangeTimeValues, true, validationExecutor);
    }

    /**
     * VerifyMinMaxValidationFailsWithLargeValues
     * @testDescription Verifies that the min and max validation (isValid) fails when a later time to the max time has been set
     */
    @Test
    public void VerifyMinMaxValidationFailsWithLargeValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_largeTimeValues, false, validationExecutor);
    }

    /**
     * VerifyMinMaxValidationFailsWithInvalidValues
     * @testDescription Verifies that the min and max validation (isValid) fails when an invalid time has been set
     */
    @Test
    public void VerifyMinMaxValidationFailsWithInvalidValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, largestInRangeValue);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMinMaxValidationFailsWithNoSetValue
     * @testDescription Verifies that the isRequired, min and max validation (isValid) fails when no time has been set
     */
    @Test
    public void VerifyRequiredMinMaxValidationFailsWithNoSetValue()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, largestInRangeValue, true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        Assert.assertFalse(timeInputHandler.isValid());
    }

    /**
     * VerifyRequiredMinMaxValidationFailsWithSmallValues
     * @testDescription Verifies that the isRequired, min and max validation (isValid) fails when a prior time to the min time has been set
     */
    @Test
    public void VerifyRequiredMinMaxValidationFailsWithSmallValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, largestInRangeValue, true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_smallTimeValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMinMaxValidationSucceedsWithInRangeValues
     * @testDescription Verifies that the isRequired, min and max validation (isValid) succeeds when a time has been set and
     * it is the same or a later time to the min time and is the same or a prior time to the max time
     */
    @Test
    public void VerifyRequiredMinMaxValidationSucceedsWithInRangeValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, largestInRangeValue, true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_inRangeTimeValues, true, validationExecutor);
    }

    /**
     * VerifyRequiredMinMaxValidationFailsWithLargeValues
     * @testDescription Verifies that the isRequired, min and max validation (isValid) fails when a later time to the max time has been set
     */
    @Test
    public void VerifyRequiredMinMaxValidationFailsWithLargeValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, largestInRangeValue, true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_largeTimeValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMinMaxValidationFailsWithInvalidValues
     * @testDescription Verifies that the min and max validation (isValid) fails when an invalid time has been set
     */
    @Test
    public void VerifyRequiredMinMaxValidationFailsWithInvalidValues()
    {
        TimeInput timeInput = createTimeInputWithValidationProperties(smallestInRangeValue, largestInRangeValue, true);
        TimeInputHandler timeInputHandler = createInputHandler(timeInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(timeInputHandler);
        TestUtil.runValidationTests(c_invalidTimeValues, false, validationExecutor);
    }

}
