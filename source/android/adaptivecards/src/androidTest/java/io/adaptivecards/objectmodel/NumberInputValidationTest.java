package io.adaptivecards.objectmodel;

import android.support.test.InstrumentationRegistry;
import android.support.v4.app.FragmentManager;
import android.widget.EditText;

import junit.framework.Assert;

import org.junit.Test;

import io.adaptivecards.renderer.inputhandler.NumberInputHandler;

public class NumberInputValidationTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    private NumberInput createNumberInputWithValidationProperties(Double min, Double max)
    {
        return createNumberInputWithValidationProperties(min, max, false);
    }

    private NumberInput createNumberInputWithValidationProperties(Double min, Double max, boolean isRequired)
    {
        NumberInput numberInput = TestUtil.createMockNumberInput();
        numberInput.SetMin(min);
        numberInput.SetMax(max);
        numberInput.SetIsRequired(isRequired);
        return numberInput;
    }

    private NumberInputHandler createInputHandler(NumberInput numberInput)
    {
        NumberInputHandler numberInputHandler = new NumberInputHandler(numberInput);
        numberInputHandler.setView(new EditText(InstrumentationRegistry.getContext()));
        return numberInputHandler;
    }

    private NumberInputHandler createCustomInputHandlerWithoutSpecificValidation(NumberInput numberInput)
    {
        class CustomNumberInputHandler extends NumberInputHandler
        {
            public CustomNumberInputHandler(BaseInputElement baseInputElement, FragmentManager fragmentManager) { super(baseInputElement); }

            @Override
            public boolean isValidOnSpecifics(String NumberInputValue) { return true; }
        }

        NumberInputHandler numberInputHandler = new CustomNumberInputHandler(numberInput, null);
        numberInputHandler.setView(new EditText(InstrumentationRegistry.getContext()));

        return numberInputHandler;
    }

    private final Double[] c_smallNumberValues = {-485239.0, -115866.0, -43089.0, -6581.0, -711.0, -264.0, -101.0};
    private final Double[] c_inRangeNumberValues = {-100.0, -80.0, -42.0, 0.0, 22.0, 57.0, 100.0};
    private final Double[] c_largeNumberValues = {101.0, 381.0, 706.0, 6778.0, 13213.0, 344586.0, 757867.0};
    private final String[] c_invalidNumberValues = {"aWord", "b", "312c", "-", ".", "4+9"};

    /**
     * VerifyIsRequiredValidationFailsWithNoSetValue
     * @testDescription Verifies that an input with isRequired = true will fail when no value has been set
     */
    @Test
    public void VerifyIsRequiredValidationFailsWithNoSetValue()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, null, true);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        Assert.assertFalse(numberInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationSucceedsWithSetValue
     * @testDescription Verifies that an input with isRequired = true will succeed when a valid number has been set
     */
    @Test
    public void VerifyIsRequiredValidationSucceedsWithSetValue()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, null, true);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(Double.class, c_smallNumberValues, c_inRangeNumberValues, c_largeNumberValues), true, validationExecutor);
    }

    /**
     * VerifyIsRequiredValidationFailsWithSetInvalidValue
     * @testDescription Verifies that an input with isRequired = true will fail when an invalid number has been set
     */
    @Test
    public void VerifyIsRequiredValidationFailsWithSetInvalidValue()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, null, true);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_invalidNumberValues, false, validationExecutor);
    }

    /**
     * VerifyOnlyIsRequiredValidationFailsWithNoSetValue
     * @testDescription Verifies that the isRequired check shared by all InputValidation classes fails when no value has been set
     */
    @Test
    public void VerifyOnlyIsRequiredValidationFailsWithNoSetValue()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, null, true);
        NumberInputHandler numberInputHandler = createCustomInputHandlerWithoutSpecificValidation(numberInput);

        Assert.assertFalse(numberInputHandler.isValid());
    }

    /**
     * VerifyOnlyIsRequiredValidationSucceedsWithSetValidValue
     * @testDescription Verifies that the isRequired check shared by all InputValidation classes fails when a valid number has been set
     */
    @Test
    public void VerifyOnlyIsRequiredValidationSucceedsWithSetValidValue()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, null, true);
        NumberInputHandler numberInputHandler = createCustomInputHandlerWithoutSpecificValidation(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(Double.class, c_smallNumberValues, c_inRangeNumberValues, c_largeNumberValues), true, validationExecutor);
    }

    /**
     * VerifyOnlyIsRequiredValidationSucceedsWithSetInvalidValue
     * @testDescription Verifies that the isRequired check shared by all InputValidation classes fails when an invalid number has been set
     */
    @Test
    public void VerifyOnlyIsRequiredValidationSucceedsWithSetInvalidValue()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, null, true);
        NumberInputHandler numberInputHandler = createCustomInputHandlerWithoutSpecificValidation(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_invalidNumberValues, true, validationExecutor);
    }

    /**
     * VerifySpecificMinValidationSucceedsWithNoSetValue
     * @testDescription Verifies that the min validation (isValidOnSpecifics) succeeds when no number
     * has been set and it's not required as there's no comparison to be made
     */
    @Test
    public void VerifySpecificMinValidationSucceedsWithNoSetValue()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], null);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        Assert.assertTrue(numberInputHandler.isValidOnSpecifics(""));
    }

    /**
     * VerifySpecificMinValidationFailsWithSmallValues
     * @testDescription Verifies that the min validation (isValidOnSpecifics) fails when a smaller number to the min number has been set
     */
    @Test
    public void VerifySpecificMinValidationFailsWithSmallValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], null);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.SpecificsValidationExecutor minValidationExecutor = new TestUtil.SpecificsValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_smallNumberValues, false, minValidationExecutor);
    }

    /**
     * VerifySpecificMinValidationSucceedsWithInRangeAndLargeValues
     * @testDescription Verifies that the min validation (isValidOnSpecifics) succeeds when the same or greater number to the min number has been set
     */
    @Test
    public void VerifySpecificMinValidationSucceedsWithInRangeAndLargeValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], null);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.SpecificsValidationExecutor minValidationExecutor = new TestUtil.SpecificsValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(Double.class, c_inRangeNumberValues, c_largeNumberValues), true, minValidationExecutor);
    }

    /**
     * VerifySpecificMinValidationFailsWithInvalidValues
     * @testDescription Verifies that the min validation (isValidOnSpecifics) fails when an invalid number has been set
     */
    @Test
    public void VerifySpecificMinValidationFailsWithInvalidValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], null);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.SpecificsValidationExecutor minValidationExecutor = new TestUtil.SpecificsValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_invalidNumberValues, false, minValidationExecutor);
    }

    /**
     * VerifyMinValidationSucceedsWithNoSetValue
     * @testDescription  Verifies that the min validation (isValid) succeeds when no number has been set
     * and it's not required as there's no comparison to be made
     */
    @Test
    public void VerifyMinValidationSucceedsWithNoSetValue()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], null);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        Assert.assertEquals(true, numberInputHandler.isValid());
    }

    /**
     * VerifyMinValidationFailsWithSmallValues
     *  @testDescription Verifies that the min validation (isValid) fails when a smaller number to the min number has been set
     */
    @Test
    public void VerifyMinValidationFailsWithSmallValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], null);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_smallNumberValues, false, validationExecutor);
    }

    /**
     * VerifyMinValidationSucceedsWithInRangeAndLargeValues
     * @testDescription Verifies that the min validation (isValid) succeeds when the same or greater number to the min number has been set
     */
    @Test
    public void VerifyMinValidationSucceedsWithInRangeAndLargeValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], null);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(Double.class, c_inRangeNumberValues, c_largeNumberValues), true, validationExecutor);
    }

    /**
     * VerifyMinValidationFailsWithInvalidValues
     * @testDescription Verifies that the min validation (isValid) fails when an invalid number has been set
     */
    @Test
    public void VerifyMinValidationFailsWithInvalidValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], null);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_invalidNumberValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMinValidationFailsWithNoSetValue
     * @testDescription Verifies that the min and isRequired validation (isValid) fails when no number has been set
     */
    @Test
    public void VerifyRequiredMinValidationFailsWithNoSetValue()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], null, true);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        Assert.assertFalse(numberInputHandler.isValid());
    }

    /**
     * VerifyRequiredMinValidationFailsWithSmallValues
     * @testDescription Verifies that the min and isRequired validation (isValid) fails when a smaller number to the min number has been set
     */
    @Test
    public void VerifyRequiredMinValidationFailsWithSmallValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], null, true);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_smallNumberValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMinValidationSucceedsWithInRangeAndLargeValues
     * @testDescription Verifies that the min and isRequired validation (isValid) succeeds when the same or greater number to the min number has been set
     */
    @Test
    public void VerifyRequiredMinValidationSucceedsWithInRangeAndLargeValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], null, true);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(Double.class, c_inRangeNumberValues, c_largeNumberValues), true, validationExecutor);
    }

    /**
     * VerifyRequiredMinValidationSucceedsWithInvalidValues
     * @testDescription Verifies that the min and isRequired validation (isValid) fails when an invalid number has been set
     */
    @Test
    public void VerifyRequiredMinValidationSucceedsWithInvalidValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], null, true);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        // Invalid number values for non required inputs are considered invalid
        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_invalidNumberValues, false, validationExecutor);
    }

    /**
     * VerifySpecificMaxValidationSucceedsWithNoSetValue
     * @testDescription Verifies that the max validation (isValidOnSpecifics) succeeds when no number has been set
     */
    @Test
    public void VerifySpecificMaxValidationSucceedsWithNoSetValue()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        Assert.assertTrue(numberInputHandler.isValidOnSpecifics(""));
    }

    /**
     * VerifySpecificMaxValidationSucceedsWithSmallAndInRangeValues
     * @testDescription Verifies that the max validation (isValidOnSpecifics) succeeds when the input
     * number is equals or less than the max number has been set
     */
    @Test
    public void VerifySpecificMaxValidationSucceedsWithSmallAndInRangeValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.SpecificsValidationExecutor maxValidationExecutor = new TestUtil.SpecificsValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(Double.class, c_smallNumberValues, c_inRangeNumberValues), true, maxValidationExecutor);
    }

    /**
     * VerifySpecificMaxValidationFailsWithLargeValues
     * @testDescription Verifies that the max validation (isValidOnSpecifics) fails when a greater number to the max number has been set
     */
    @Test
    public void VerifySpecificMaxValidationFailsWithLargeValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.SpecificsValidationExecutor maxValidationExecutor = new TestUtil.SpecificsValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_largeNumberValues, false, maxValidationExecutor);
    }

    /**
     * VerifySpecificMaxValidationFailsWithInvalidValues
     * @testDescription Verifies that the max validation (isValidOnSpecifics) fails when an invalid number has been set
     */
    @Test
    public void VerifySpecificMaxValidationFailsWithInvalidValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.SpecificsValidationExecutor maxValidationExecutor = new TestUtil.SpecificsValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_invalidNumberValues, false, maxValidationExecutor);
    }

    /**
     * VerifyMaxValidationSucceedsWithNoSetValue
     * @testDescription  Verifies that the max validation (isValid) succeeds when no number has been set
     * and it's not required as there's no comparison to be made
     */
    @Test
    public void VerifyMaxValidationSucceedsWithNoSetValue()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        Assert.assertTrue(numberInputHandler.isValid());
    }

    /**
     * VerifyMaxValidationSucceedsWithSmallAndInRangeValues
     * @testDescription Verifies that the max validation (isValid) succeeds when the input number is equals or less than the max number
     */
    @Test
    public void VerifyMaxValidationSucceedsWithSmallAndInRangeValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(Double.class, c_smallNumberValues, c_inRangeNumberValues), true, validationExecutor);
    }

    /**
     * VerifyMaxValidationSucceedsWithLargeValues
     * @testDescription Verifies that the max validation (isValid) fails when a greater number to the max number has been set
     */
    @Test
    public void VerifyMaxValidationSucceedsWithLargeValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_largeNumberValues, false, validationExecutor);
    }

    /**
     * VerifyMaxValidationFailsWithInvalidValues
     * @testDescription Verifies that the max validation (isValid) fails when an invalid number has been set
     */
    @Test
    public void VerifyMaxValidationFailsWithInvalidValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_invalidNumberValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMaxValidationFailsWithNoSetValue
     * @testDescription  Verifies that the max and isRequired validation (isValid) fails when no number has been set
     */
    @Test
    public void VerifyRequiredMaxValidationFailsWithNoSetValue()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, c_inRangeNumberValues[c_inRangeNumberValues.length - 1], true);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        Assert.assertFalse(numberInputHandler.isValid());
    }

    /**
     * VerifyRequiredMaxValidationSucceedsWithSmallAndInRangeValues
     * @testDescription  Verifies that the max and isRequired validation (isValid) succeeds when the
     * input value is equals or less than the max number has been set
     */
    @Test
    public void VerifyRequiredMaxValidationSucceedsWithSmallAndInRangeValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, c_inRangeNumberValues[c_inRangeNumberValues.length - 1], true);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(Double.class, c_smallNumberValues, c_inRangeNumberValues), true, validationExecutor);
    }

    /**
     * VerifyRequiredMaxValidationFailsWithLargeValues
     * @testDescription  Verifies that the max and isRequired validation (isValid) fail when a greater number to the max number has been set
     */
    @Test
    public void VerifyRequiredMaxValidationFailsWithLargeValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, c_inRangeNumberValues[c_inRangeNumberValues.length - 1], true);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_largeNumberValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMaxValidationFailsWithInvalidValues
     * @testDescription  Verifies that the max and isRequired validation (isValid) fail when an invalid number has been set
     */
    @Test
    public void VerifyRequiredMaxValidationFailsWithInvalidValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(null, c_inRangeNumberValues[c_inRangeNumberValues.length - 1], true);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_invalidNumberValues, false, validationExecutor);
    }

    /**
     * VerifySpecificMinMaxValidationSucceedsWithNoSetValue
     * @testDescription Verifies that the min and max validation (isValidOnSpecifics) succeeds when no number has been set
     */
    @Test
    public void VerifySpecificMinMaxValidationSucceedsWithNoSetValue()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        Assert.assertTrue(numberInputHandler.isValidOnSpecifics(""));
    }

    /**
     * VerifySpecificMinMaxValidationFailsWithSmallValues
     * @testDescription Verifies that the min and max validation (isValidOnSpecifics) fails when a smaller number to the min number has been set
     */
    @Test
    public void VerifySpecificMinMaxValidationFailsWithSmallValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.SpecificsValidationExecutor minMaxValidationExecutor = new TestUtil.SpecificsValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_smallNumberValues, false, minMaxValidationExecutor);
    }

    /**
     * VerifySpecificMinMaxValidationSucceedsWithInRangeValues
     * @testDescription Verifies that the min and max validation (isValidOnSpecifics) succeeds when
     * the input number is greater or equals than the min number and is the less or equals than the max number
     */
    @Test
    public void VerifySpecificMinMaxValidationSucceedsWithInRangeValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.SpecificsValidationExecutor minMaxValidationExecutor = new TestUtil.SpecificsValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_inRangeNumberValues, true, minMaxValidationExecutor);
    }

    /**
     * VerifySpecificMinMaxValidationFailsWithLargeValues
     * @testDescription Verifies that the min and max validation (isValidOnSpecifics) fails when a greater number to the max number has been set
     */
    @Test
    public void VerifySpecificMinMaxValidationFailsWithLargeValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.SpecificsValidationExecutor minMaxValidationExecutor = new TestUtil.SpecificsValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_largeNumberValues, false, minMaxValidationExecutor);
    }

    /**
     * VerifySpecificMinMaxValidationFailsWithInvalidValues
     * @testDescription Verifies that the min and max validation (isValidOnSpecifics) fails when an invalid number has been set
     */
    @Test
    public void VerifySpecificMinMaxValidationFailsWithInvalidValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.SpecificsValidationExecutor minMaxValidationExecutor = new TestUtil.SpecificsValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_invalidNumberValues, false, minMaxValidationExecutor);
    }

    /**
     * VerifyMinMaxValidationFailsWithNoSetValue
     * @testDescription Verifies that the min and max validation (isValid) succeeds when no number has been set
     */
    @Test
    public void VerifyMinMaxValidationSucceedsWithNoSetValue()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        Assert.assertTrue(numberInputHandler.isValid());
    }

    /**
     * VerifyMinMaxValidationFailsWithSmallValues
     * @testDescription Verifies that the min and max validation (isValid) fails when a smaller number to the min number has been set
     */
    @Test
    public void VerifyMinMaxValidationFailsWithSmallValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_smallNumberValues, false, validationExecutor);
    }

    /**
     * VerifyMinMaxValidationSucceedsWithInRangeValues
     * @testDescription Verifies that the min and max validation (isValid) succeeds when the input value
     * is greater or equals than the min number and is the less or equals than the max number
     */
    @Test
    public void VerifyMinMaxValidationSucceedsWithInRangeValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_inRangeNumberValues, true, validationExecutor);
    }

    /**
     * VerifyMinMaxValidationFailsWithLargeValues
     * @testDescription Verifies that the min and max validation (isValid) fails when a greater number to the max number has been set
     */
    @Test
    public void VerifyMinMaxValidationFailsWithLargeValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_largeNumberValues, false, validationExecutor);
    }

    /**
     * VerifyMinMaxValidationFailsWithInvalidValues
     * @testDescription Verifies that the min and max validation (isValid) fails when an invalid number has been set
     */
    @Test
    public void VerifyMinMaxValidationFailsWithInvalidValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], c_inRangeNumberValues[c_inRangeNumberValues.length - 1]);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_invalidNumberValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMinMaxValidationFailsWithNoSetValue
     * @testDescription Verifies that the isRequired, min and max validation (isValid) fails when no number has been set
     */
    @Test
    public void VerifyRequiredMinMaxValidationFailsWithNoSetValue()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], c_inRangeNumberValues[c_inRangeNumberValues.length - 1], true);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        Assert.assertFalse(numberInputHandler.isValid());
    }

    /**
     * VerifyRequiredMinMaxValidationFailsWithSmallValues
     * @testDescription Verifies that the isRequired, min and max validation (isValid) fails when a smaller number to the min number has been set
     */
    @Test
    public void VerifyRequiredMinMaxValidationFailsWithSmallValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], c_inRangeNumberValues[c_inRangeNumberValues.length - 1], true);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_smallNumberValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMinMaxValidationSucceedsWithInRangeValues
     * @testDescription Verifies that the isRequired, min and max validation (isValid) succeeds when
     * the input value is greater or equals than min value and is less or equals than the max value
     */
    @Test
    public void VerifyRequiredMinMaxValidationSucceedsWithInRangeValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], c_inRangeNumberValues[c_inRangeNumberValues.length - 1], true);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_inRangeNumberValues, true, validationExecutor);
    }

    /**
     * VerifyRequiredMinMaxValidationFailsWithLargeValues
     * @testDescription Verifies that the isRequired, min and max validation (isValid) fails when a greater number to the max number has been set
     */
    @Test
    public void VerifyRequiredMinMaxValidationFailsWithLargeValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], c_inRangeNumberValues[c_inRangeNumberValues.length - 1], true);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_largeNumberValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredMinMaxValidationFailsWithInvalidValues
     * @testDescription Verifies that the min and max validation (isValid) fails when an invalid number has been set
     */
    @Test
    public void VerifyRequiredMinMaxValidationFailsWithInvalidValues()
    {
        NumberInput numberInput = createNumberInputWithValidationProperties(c_inRangeNumberValues[0], c_inRangeNumberValues[c_inRangeNumberValues.length - 1], true);
        NumberInputHandler numberInputHandler = createInputHandler(numberInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(numberInputHandler);
        TestUtil.runValidationTests(c_invalidNumberValues, false, validationExecutor);
    }

}
