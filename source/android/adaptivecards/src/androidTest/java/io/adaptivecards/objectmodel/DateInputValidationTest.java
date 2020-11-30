package io.adaptivecards.objectmodel;

import android.support.test.InstrumentationRegistry;
import android.support.v4.app.FragmentManager;
import android.widget.EditText;

import junit.framework.Assert;

import org.junit.Test;
import org.junit.runner.Description;

import io.adaptivecards.renderer.inputhandler.DateInputHandler;

public class DateInputValidationTest
{
    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    private DateInput createDateInputWithValidationProperties(String minDate, String maxDate)
    {
        return createDateInputWithValidationProperties(minDate, maxDate, false);
    }

    private DateInput createDateInputWithValidationProperties(String minDate, String maxDate, boolean isRequired)
    {
        DateInput dateInput = TestUtil.createMockDateInput();
        dateInput.SetMin(minDate);
        dateInput.SetMax(maxDate);
        dateInput.SetIsRequired(isRequired);
        return dateInput;
    }

    private DateInputHandler createInputHandler(DateInput dateInput)
    {
        DateInputHandler dateInputHandler = new DateInputHandler(dateInput, null);
        dateInputHandler.setView(new EditText(InstrumentationRegistry.getContext()));
        return dateInputHandler;
    }

    private DateInputHandler createCustomInputHandlerWithoutSpecificValidation(DateInput dateInput)
    {
        class CustomDateInputHandler extends DateInputHandler
        {
            public CustomDateInputHandler(BaseInputElement baseInputElement, FragmentManager fragmentManager) { super(baseInputElement, fragmentManager); }

            @Override
            public boolean isValidOnSpecifics(String dateInputValue) { return true; }
        }

        DateInputHandler dateInputHandler = new CustomDateInputHandler(dateInput, null);
        dateInputHandler.setView(new EditText(InstrumentationRegistry.getContext()));

        return dateInputHandler;
    }

    private final String[] c_smallDateValues = {"1994-07-24", "1995-05-18", "1995-05-26", "1996-11-26", "1996-11-29", "1997-08-30", "1998-03-09"};
    private final String[] c_inRangeDateValues = {"1998-03-10", "1999-03-03", "1999-11-08", "2002-01-21", "2005-03-22", "2005-10-21", "2007-09-05"};
    private final String[] c_largeDateValues = {"2007-09-06", "2010-09-14", "2011-08-30", "2011-10-19", "2017-10-21", "2017-11-07", "2018-08-14"};
    private final String[] c_invalidDateValues = {"aWord", "12-12-2012", "12:02", "2011/08/30", "2013-13-13", "a-b-c", "7."};

    /**
     * VerifyIsRequiredValidationFailsWithNoSetValue
     * @testDescription Verifies that an input with isRequired = true will fail when no value has been set
     */
    @Test
    public void VerifyIsRequiredValidationFailsWithNoSetValue()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", "", true);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        Assert.assertFalse(dateInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationSucceedsWithSetValue
     * @testDescription Verifies that an input with isRequired = true will succeed when a valid date has been set
     */
    @Test
    public void VerifyIsRequiredValidationSucceedsWithSetValue()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", "", true);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallDateValues, c_inRangeDateValues, c_largeDateValues), true, validationExecutor);
    }

    /**
     * VerifyIsRequiredValidationFailsWithSetInvalidValue
     * @testDescription Verifies that an input with isRequired = true will fail when an invalid date has been set
     */
    @Test
    public void VerifyIsRequiredValidationFailsWithSetInvalidValue()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", "", true);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_invalidDateValues, false, validationExecutor);
    }

    /**
     * VerifyOnlyIsRequiredValidationFailsWithNoSetValue
     * @testDescription Verifies that the isRequired check shared by all InputValidation classes fails when no value has been set
     */
    @Test
    public void VerifyOnlyIsRequiredValidationFailsWithNoSetValue()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", "", true);
        DateInputHandler dateInputHandler = createCustomInputHandlerWithoutSpecificValidation(dateInput);

        Assert.assertFalse(dateInputHandler.isValid());
    }

    /**
     * VerifyOnlyIsRequiredValidationSucceedsWithSetValidValue
     * @testDescription Verifies that the isRequired check shared by all InputValidation classes fails when a valid date has been set
     */
    @Test
    public void VerifyOnlyIsRequiredValidationSucceedsWithSetValidValue()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", "", true);
        DateInputHandler dateInputHandler = createCustomInputHandlerWithoutSpecificValidation(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallDateValues, c_inRangeDateValues, c_largeDateValues), true, validationExecutor);
    }

    /**
     * VerifyOnlyIsRequiredValidationSucceedsWithSetInvalidValue
     * @testDescription Verifies that the isRequired check shared by all InputValidation classes fails when an invalid date has been set
     */
    @Test
    public void VerifyOnlyIsRequiredValidationSucceedsWithSetInvalidValue()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", "", true);
        DateInputHandler dateInputHandler = createCustomInputHandlerWithoutSpecificValidation(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_invalidDateValues, true, validationExecutor);
    }

    /**
     * VerifySpecificMinValidationSucceedsWithNoSetValue
     * @testDescription Verifies that the min validation (isValidOnSpecifics) succeeds when no date
     * has been set and it's not required as there's no comparison to be made
     */
    @Test
    public void VerifySpecificMinValidationSucceedsWithNoSetValue()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], "");
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        Assert.assertTrue(dateInputHandler.isValidOnSpecifics(""));
    }

    /**
     * VerifySpecificMinValidationFailsWithSmallValues
     * @testDescription Verifies that the min validation (isValidOnSpecifics) fails when a prior date to the min date has been set
     */
    @Test
    public void VerifySpecificMinValidationFailsWithSmallValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], "");
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.SpecificsValidationExecutor minValidationExecutor = new TestUtil.SpecificsValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_smallDateValues, false, minValidationExecutor);
    }

    /**
     * VerifySpecificMinValidationSucceedsWithInRangeAndLargeValues
     * @testDescription Verifies that the min validation (isValidOnSpecifics) succeeds when the same or later date to the min date has been set
     */
    @Test
    public void VerifySpecificMinValidationSucceedsWithInRangeAndLargeValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], "");
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.SpecificsValidationExecutor minValidationExecutor = new TestUtil.SpecificsValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_inRangeDateValues, c_largeDateValues), true, minValidationExecutor);
    }

    /**
     * VerifySpecificMinValidationFailsWithInvalidValues
     * @testDescription Verifies that the min validation (isValidOnSpecifics) fails when an invalid date has been set
     */
    @Test
    public void VerifySpecificMinValidationFailsWithInvalidValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], "");
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.SpecificsValidationExecutor minValidationExecutor = new TestUtil.SpecificsValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_invalidDateValues, false, minValidationExecutor);
    }

    /**
     * VerifyMinValidationSucceedsWithNoSetValue
     * @testDescription  Verifies that the min validation (isValid) succeeds when no date has been set
     * and it's not required as there's no comparison to be made
     */
    @Test
    public void VerifyMinValidationSucceedsWithNoSetValue()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], "");
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        Assert.assertEquals(true, dateInputHandler.isValid());
    }

    /**
     * VerifyMinValidationFailsWithSmallValues
     *  @testDescription Verifies that the min validation (isValid) fails when a prior date to the min date has been set
     */
    @Test
    public void VerifyMinValidationFailsWithSmallValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], "");
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_smallDateValues, false, validationExecutor);
    }

    /**
     * VerifyMinValidationSucceedsWithInRangeAndLargeValues
     * @testDescription Verifies that the min validation (isValid) succeeds when the same or later date to the min date has been set
     */
    @Test
    public void VerifyMinValidationSucceedsWithInRangeAndLargeValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], "");
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_inRangeDateValues, c_largeDateValues), true, validationExecutor);
    }

    /**
     * VerifyMinValidationFailsWithInvalidValues
     * @testDescription Verifies that the min validation (isValid) fails when an invalid date has been set
     */
    @Test
    public void VerifyMinValidationFailsWithInvalidValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], "");
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_invalidDateValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMinValidationFailsWithNoSetValue
     * @testDescription Verifies that the min and isRequired validation (isValid) fails when no date has been set
     */
    @Test
    public void VerifyRequiredMinValidationFailsWithNoSetValue()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], "", true);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        Assert.assertFalse(dateInputHandler.isValid());
    }

    /**
     * VerifyRequiredMinValidationFailsWithSmallValues
     * @testDescription Verifies that the min and isRequired validation (isValid) fails when a prior date to the min date has been set
     */
    @Test
    public void VerifyRequiredMinValidationFailsWithSmallValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], "", true);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_smallDateValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMinValidationSucceedsWithInRangeAndLargeValues
     * @testDescription Verifies that the min and isRequired validation (isValid) succeeds when the same or later date to the min date has been set
     */
    @Test
    public void VerifyRequiredMinValidationSucceedsWithInRangeAndLargeValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], "", true);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_inRangeDateValues, c_largeDateValues), true, validationExecutor);
    }

    /**
     * VerifyRequiredMinValidationSucceedsWithInvalidValues
     * @testDescription Verifies that the min and isRequired validation (isValid) fails when an invalid date has been set
     */
    @Test
    public void VerifyRequiredMinValidationSucceedsWithInvalidValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], "", true);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        // Invalid date values for non required inputs are considered invalid
        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_invalidDateValues, false, validationExecutor);
    }

    /**
     * VerifySpecificMaxValidationSucceedsWithNoSetValue
     * @testDescription Verifies that the max validation (isValidOnSpecifics) succeeds when no date has been set
     */
    @Test
    public void VerifySpecificMaxValidationSucceedsWithNoSetValue()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        Assert.assertTrue(dateInputHandler.isValidOnSpecifics(""));
    }

    /**
     * VerifySpecificMaxValidationSucceedsWithSmallAndInRangeValues
     * @testDescription Verifies that the max validation (isValidOnSpecifics) succeeds when same
     * or prior date to the max date has been set
     */
    @Test
    public void VerifySpecificMaxValidationSucceedsWithSmallAndInRangeValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.SpecificsValidationExecutor maxValidationExecutor = new TestUtil.SpecificsValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallDateValues, c_inRangeDateValues), true, maxValidationExecutor);
    }

    /**
     * VerifySpecificMaxValidationFailsWithLargeValues
     * @testDescription Verifies that the max validation (isValidOnSpecifics) fails when a later date to the max date has been set
     */
    @Test
    public void VerifySpecificMaxValidationFailsWithLargeValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.SpecificsValidationExecutor maxValidationExecutor = new TestUtil.SpecificsValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_largeDateValues, false, maxValidationExecutor);
    }

    /**
     * VerifySpecificMaxValidationFailsWithInvalidValues
     * @testDescription Verifies that the max validation (isValidOnSpecifics) fails when an invalid date has been set
     */
    @Test
    public void VerifySpecificMaxValidationFailsWithInvalidValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.SpecificsValidationExecutor maxValidationExecutor = new TestUtil.SpecificsValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_invalidDateValues, false, maxValidationExecutor);
    }

    /**
     * VerifyMaxValidationSucceedsWithNoSetValue
     * @testDescription  Verifies that the max validation (isValid) succeeds when no date has been set
     * and it's not required as there's no comparison to be made
     */
    @Test
    public void VerifyMaxValidationSucceedsWithNoSetValue()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        Assert.assertTrue(dateInputHandler.isValid());
    }

    /**
     * VerifyMaxValidationSucceedsWithSmallAndInRangeValues
     * @testDescription Verifies that the max validation (isValid) succeeds when the same or a prior date to the max date has been set
     */
    @Test
    public void VerifyMaxValidationSucceedsWithSmallAndInRangeValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallDateValues, c_inRangeDateValues), true, validationExecutor);
    }

    /**
     * VerifyMaxValidationSucceedsWithLargeValues
     * @testDescription Verifies that the max validation (isValid) fails when a later date to the max date has been set
     */
    @Test
    public void VerifyMaxValidationSucceedsWithLargeValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_largeDateValues, false, validationExecutor);
    }

    /**
     * VerifyMaxValidationFailsWithInvalidValues
     * @testDescription Verifies that the max validation (isValid) fails when an invalid date has been set
     */
    @Test
    public void VerifyMaxValidationFailsWithInvalidValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_invalidDateValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMaxValidationFailsWithNoSetValue
     * @testDescription  Verifies that the max and isRequired validation (isValid) fails when no date has been set
     */
    @Test
    public void VerifyRequiredMaxValidationFailsWithNoSetValue()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", c_inRangeDateValues[c_inRangeDateValues.length - 1], true);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        Assert.assertFalse(dateInputHandler.isValid());
    }

    /**
     * VerifyRequiredMaxValidationSucceedsWithSmallAndInRangeValues
     * @testDescription  Verifies that the max and isRequired validation (isValid) succeeds when the same
     * or a prior date to the max date has been set
     */
    @Test
    public void VerifyRequiredMaxValidationSucceedsWithSmallAndInRangeValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", c_inRangeDateValues[c_inRangeDateValues.length - 1], true);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_smallDateValues, c_inRangeDateValues), true, validationExecutor);
    }

    /**
     * VerifyRequiredMaxValidationFailsWithLargeValues
     * @testDescription  Verifies that the max and isRequired validation (isValid) fail when a later date to the max date has been set
     */
    @Test
    public void VerifyRequiredMaxValidationFailsWithLargeValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", c_inRangeDateValues[c_inRangeDateValues.length - 1], true);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_largeDateValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMaxValidationFailsWithInvalidValues
     * @testDescription  Verifies that the max and isRequired validation (isValid) fail when an invalid date has been set
     */
    @Test
    public void VerifyRequiredMaxValidationFailsWithInvalidValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties("", c_inRangeDateValues[c_inRangeDateValues.length - 1], true);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_invalidDateValues, false, validationExecutor);
    }

    /**
     * VerifySpecificMinMaxValidationSucceedsWithNoSetValue
     * @testDescription Verifies that the min and max validation (isValidOnSpecifics) succeeds when no date has been set
     */
    @Test
    public void SpecificMinMaxValidationForNonRequiredAndEmptyInputTest()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        Assert.assertTrue(dateInputHandler.isValidOnSpecifics(""));
    }

    /**
     * VerifySpecificMinMaxValidationFailsWithSmallValues
     * @testDescription Verifies that the min and max validation (isValidOnSpecifics) fails when a prior date to the min date has been set
     */
    @Test
    public void VerifySpecificMinMaxValidationFailsWithSmallValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.SpecificsValidationExecutor minMaxValidationExecutor = new TestUtil.SpecificsValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_smallDateValues, false, minMaxValidationExecutor);
    }

    /**
     * VerifySpecificMinMaxValidationSucceedsWithInRangeValues
     * @testDescription Verifies that the min and max validation (isValidOnSpecifics) succeeds when a
     * date has been set and it is the same or a later date to the min date and is the same or a prior
     * date to the max date
     */
    @Test
    public void VerifySpecificMinMaxValidationSucceedsWithInRangeValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.SpecificsValidationExecutor minMaxValidationExecutor = new TestUtil.SpecificsValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_inRangeDateValues, true, minMaxValidationExecutor);
    }

    /**
     * VerifySpecificMinMaxValidationFailsWithLargeValues
     * @testDescription Verifies that the min and max validation (isValidOnSpecifics) fails when a later date to the max date has been set
     */
    @Test
    public void VerifySpecificMinMaxValidationFailsWithLargeValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.SpecificsValidationExecutor minMaxValidationExecutor = new TestUtil.SpecificsValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_largeDateValues, false, minMaxValidationExecutor);
    }

    /**
     * VerifySpecificMinMaxValidationFailsWithInvalidValues
     * @testDescription Verifies that the min and max validation (isValidOnSpecifics) fails when an invalid date has been set
     */
    @Test
    public void VerifySpecificMinMaxValidationFailsWithInvalidValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.SpecificsValidationExecutor minMaxValidationExecutor = new TestUtil.SpecificsValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_invalidDateValues, false, minMaxValidationExecutor);
    }

    /**
     * VerifyMinMaxValidationFailsWithNoSetValue
     * @testDescription Verifies that the min and max validation (isValid) succeeds when no date has been set
     */
    @Test
    public void VerifyMinMaxValidationSucceedsWithNoSetValue()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        Assert.assertTrue(dateInputHandler.isValid());
    }

    /**
     * VerifyMinMaxValidationFailsWithSmallValues
     * @testDescription Verifies that the min and max validation (isValid) fails when a prior date to the min date has been set
     */
    @Test
    public void VerifyMinMaxValidationFailsWithSmallValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_smallDateValues, false, validationExecutor);
    }

    /**
     * VerifyMinMaxValidationSucceedsWithInRangeValues
     * @testDescription Verifies that the min and max validation (isValid) succeeds when a date has been set and
     * it is the same or a later date to the min date and is the same or a prior date to the max date
     */
    @Test
    public void VerifyMinMaxValidationSucceedsWithInRangeValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_inRangeDateValues, true, validationExecutor);
    }

    /**
     * VerifyMinMaxValidationFailsWithLargeValues
     * @testDescription Verifies that the min and max validation (isValid) fails when a later date to the max date has been set
     */
    @Test
    public void VerifyMinMaxValidationFailsWithLargeValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_largeDateValues, false, validationExecutor);
    }

    /**
     * VerifyMinMaxValidationFailsWithInvalidValues
     * @testDescription Verifies that the min and max validation (isValid) fails when an invalid date has been set
     */
    @Test
    public void VerifyMinMaxValidationFailsWithInvalidValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], c_inRangeDateValues[c_inRangeDateValues.length - 1]);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_invalidDateValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMinMaxValidationFailsWithNoSetValue
     * @testDescription Verifies that the isRequired, min and max validation (isValid) fails when no date has been set
     */
    @Test
    public void VerifyRequiredMinMaxValidationFailsWithNoSetValue()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], c_inRangeDateValues[c_inRangeDateValues.length - 1], true);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        Assert.assertFalse(dateInputHandler.isValid());
    }

    /**
     * VerifyRequiredMinMaxValidationFailsWithSmallValues
     * @testDescription Verifies that the isRequired, min and max validation (isValid) fails when a prior date to the min date has been set
     */
    @Test
    public void VerifyRequiredMinMaxValidationFailsWithSmallValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], c_inRangeDateValues[c_inRangeDateValues.length - 1], true);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_smallDateValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMinMaxValidationSucceedsWithInRangeValues
     * @testDescription Verifies that the isRequired, min and max validation (isValid) succeeds when a date has been set and
     * it is the same or a later date to the min date and is the same or a prior date to the max date
     */
    @Test
    public void VerifyRequiredMinMaxValidationSucceedsWithInRangeValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], c_inRangeDateValues[c_inRangeDateValues.length - 1], true);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_inRangeDateValues, true, validationExecutor);
    }

    /**
     * VerifyRequiredMinMaxValidationFailsWithLargeValues
     * @testDescription Verifies that the isRequired, min and max validation (isValid) fails when a later date to the max date has been set
     */
    @Test
    public void VerifyRequiredMinMaxValidationFailsWithLargeValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], c_inRangeDateValues[c_inRangeDateValues.length - 1], true);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_largeDateValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMinMaxValidationFailsWithInvalidValues
     * @testDescription Verifies that the min and max validation (isValid) fails when an invalid date has been set
     */
    @Test
    public void VerifyRequiredMinMaxValidationFailsWithInvalidValues()
    {
        DateInput dateInput = createDateInputWithValidationProperties(c_inRangeDateValues[0], c_inRangeDateValues[c_inRangeDateValues.length - 1], true);
        DateInputHandler dateInputHandler = createInputHandler(dateInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(dateInputHandler);
        TestUtil.runValidationTests(c_invalidDateValues, false, validationExecutor);
    }

}
