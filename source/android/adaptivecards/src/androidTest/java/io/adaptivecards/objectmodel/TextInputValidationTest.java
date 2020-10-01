package io.adaptivecards.objectmodel;

import android.support.test.InstrumentationRegistry;
import android.support.v4.app.FragmentManager;
import android.widget.EditText;

import junit.framework.Assert;

import org.junit.Test;

import io.adaptivecards.renderer.inputhandler.NumberInputHandler;
import io.adaptivecards.renderer.inputhandler.TextInputHandler;

public class TextInputValidationTest
{
    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    private final String[] c_shortStrings = {"short", "words", "are", "really", "cool!"};
    private final String[] c_longStrings = {"largerer", "worders", "are way", "bettter!!!", "looooooooooooooong word is long"};
    private final String[] c_regexInvalidValues = {"0x", "hjasdg", "0xSJKDHNASD", "0x1234m", "12123", "x978ab", "0x89723-]"};
    private final String[] c_regexValidValues = {"0x0", "0xab1", "0xabc", "0x123", "0x1D2A6E", "0x978ab" ,"0x1234567890abcdefABCDEF"};
    private final String testRegexHexColor = "^0x[0-9A-Fa-f]+$";
    private final int testMaxLength = 6;

    // For this test case let's check a hex value with a min Length of 6 (using a regex) and a maxLength ten chars long
    private final int testMaxLengthHexColor = 10;
    private final String testRegexHexColorMinLength = "^0x[0-9A-Fa-f]{4,}$";
    private final String[] shortHexColors = {"0x", "0x0", "0x12", "0x123"};
    private final String[] validHexColors = {"0x1234", "0xa12b3", "0xEDF123", "0x1aB2cD3", "0xffFFffFF"};
    private final String[] longHexColors = {"0x1234567890", "0xabcdef12345", "0xFEDCBAabcdef", "0xabcdefABCDEF0123456789"};
    private final String[] invalidHexColors = {"kjashd", "0asjkhasdj", "a", "1234345", "70%", "65$", "anEmail@internet.com"};

    private TextInput createTextInputWithValidationProperties(String regex, int maxLength)
    {
        return createTextInputWithValidationProperties(regex, maxLength, false);
    }

    private TextInput createTextInputWithValidationProperties(String regex, int maxLength, boolean isRequired)
    {
        TextInput textInput = TestUtil.createMockTextInput();
        textInput.SetRegex(regex);
        textInput.SetMaxLength(maxLength);
        textInput.SetIsRequired(isRequired);
        return  textInput;
    }

    private TextInputHandler createTextInputHandler(TextInput textInput)
    {
        TextInputHandler textInputHandler = new TextInputHandler(textInput);
        textInputHandler.setView(new EditText(InstrumentationRegistry.getContext()));
        return textInputHandler;
    }

    private TextInputHandler createCustomInputHandlerWithoutSpecificValidation(TextInput textInput)
    {
        class CustomTextInputHandler extends TextInputHandler
        {
            public CustomTextInputHandler(BaseInputElement baseInputElement) { super(baseInputElement); }

            @Override
            public boolean isValidOnSpecifics(String NumberInputValue) { return true; }
        }

        TextInputHandler textInputHandler = new CustomTextInputHandler(textInput);
        textInputHandler.setView(new EditText(InstrumentationRegistry.getContext()));

        return textInputHandler;
    }

    /**
     * VerifyIsRequiredValidationFailsWithNoSetValue
     * @testDescription Verifies that a not required input will succeed when no value has been set
     */
    @Test
    public void VerifyValidationSucceedsWithNoSetValue()
    {
        TextInput textInput = createTextInputWithValidationProperties("", 0);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        Assert.assertTrue(textInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationSucceedsWithSetValue
     * @testDescription Verifies that a not required input will succeed with any value set
     */
    @Test
    public void VerifyValidationSucceedsWithSetValue()
    {
        TextInput textInput = createTextInputWithValidationProperties("", 0, true);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_regexValidValues, c_regexInvalidValues, c_shortStrings, c_longStrings), true, validationExecutor);
    }

    /**
     * VerifyIsRequiredValidationFailsWithNoSetValue
     * @testDescription Verifies that a required input will fail when no value has been set
     */
    @Test
    public void VerifyIsRequiredValidationFailsWithNoSetValue()
    {
        TextInput textInput = createTextInputWithValidationProperties("", 0, true);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        Assert.assertFalse(textInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationSucceedsWithSetValue
     * @testDescription Verifies that a required input will succeed with any value set
     */
    @Test
    public void VerifyIsRequiredValidationSucceedsWithSetValue()
    {
        TextInput textInput = createTextInputWithValidationProperties("", 0, true);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_regexValidValues, c_regexInvalidValues, c_shortStrings, c_longStrings), true, validationExecutor);
    }

    /**
     * VerifyOnlyIsRequiredValidationFailsWithNoSetValue
     * @testDescription Verifies that the isRequired check shared by all InputValidation classes fails when no value has been set
     */
    @Test
    public void VerifyOnlyIsRequiredValidationFailsWithNoSetValue()
    {
        TextInput textInput = createTextInputWithValidationProperties("", 0, true);
        TextInputHandler textInputHandler = createCustomInputHandlerWithoutSpecificValidation(textInput);

        Assert.assertFalse(textInputHandler.isValid());
    }

    /**
     * VerifyOnlyIsRequiredValidationSucceedsWithSetValidValue
     * @testDescription Verifies that the isRequired check shared by all InputValidation classes fails when a valid number has been set
     */
    @Test
    public void VerifyOnlyIsRequiredValidationSucceedsWithSetValue()
    {
        TextInput textInput = createTextInputWithValidationProperties("", 0, true);
        TextInputHandler textInputHandler = createCustomInputHandlerWithoutSpecificValidation(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(TestUtil.concat(String.class, c_regexValidValues, c_regexInvalidValues, c_shortStrings, c_longStrings), true, validationExecutor);
    }

    /**
     * VerifySpecificRegexValidationSucceedsWithNoSetValue
     * @testDescription Verifies that the regex validation (isValidOnSpecifics) succeeds when no string
     * has been set and it's not required
     */
    @Test
    public void VerifySpecificRegexValidationSucceedsWithNoSetValue()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColor, 0);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        Assert.assertTrue(textInputHandler.isValidOnSpecifics(""));
    }

    /**
     * VerifySpecificRegexValidationFailsWithNonCompliantValues
     * @testDescription Verifies that the regex validation (isValidOnSpecifics) fails when a value doesn't
     * comply with the regex
     */
    @Test
    public void VerifySpecificRegexValidationFailsWithNonCompliantValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColor, 0);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.SpecificsValidationExecutor regexValidationExecutor = new TestUtil.SpecificsValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(c_regexInvalidValues, false, regexValidationExecutor);
    }

    /**
     * VerifySpecificRegexValidationSucceedsWithCompliantValues
     * @testDescription Verifies that the min validation (isValidOnSpecifics) succeeds when a value
     * complies with the regex
     */
    @Test
    public void VerifySpecificRegexValidationSucceedsWithCompliantValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColor, 0);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.SpecificsValidationExecutor regexValidationExecutor = new TestUtil.SpecificsValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(c_regexValidValues, true, regexValidationExecutor);
    }

    /**
     * VerifyRegexValidationSucceedsWithNoSetValue
     * @testDescription  Verifies that the regex validation (isValid) succeeds when no value has been set
     * and it's not required
     */
    @Test
    public void VerifyRegexValidationSucceedsWithNoSetValue()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColor, 0);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        Assert.assertEquals(true, textInputHandler.isValid());
    }

    /**
     * VerifyRegexValidationFailsWithNonCompliantValues
     *  @testDescription Verifies that the regex validation (isValid) fails when a value that doesn't
     *  comply with the regex has been set
     */
    @Test
    public void VerifyRegexValidationFailsWithNonCompliantValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColor, 0);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(c_regexInvalidValues, false, validationExecutor);
    }

    /**
     * VerifyRegexValidationSucceedsWithCompliantValues
     * @testDescription Verifies that the min validation (isValid) succeeds when the same or later number to the min number has been set
     */
    @Test
    public void VerifyRegexValidationSucceedsWithCompliantValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColor, 0);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(c_regexValidValues, true, validationExecutor);
    }

    /**
     * VerifyRequiredRegexValidationFailsWithNoSetValue
     * @testDescription Verifies that the regex and isRequired validation (isValid) fails when no value has been set
     */
    @Test
    public void VerifyRequiredRegexValidationFailsWithNoSetValue()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColor, 0, true);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        Assert.assertFalse(textInputHandler.isValid());
    }

    /**
     * VerifyRequiredRegexValidationFailsWithNonCompliantValues
     * @testDescription Verifies that the regex and isRequired validation (isValid) fails when a value
     * that doesn't comply with the regex has been set
     */
    @Test
    public void VerifyRequiredRegexValidationFailsWithNonCompliantValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColor, 0, true);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(c_regexInvalidValues, false, validationExecutor);
    }

    /**
     * VerifyRequiredRegexValidationSucceedsWithCompliantValues
     * @testDescription Verifies that the regex and isRequired validation (isValid) succeeds when a value
     * that complies with the regex has been set
     */
    @Test
    public void VerifyRequiredRegexValidationSucceedsWithCompliantValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColor, 0, true);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(c_regexValidValues, true, validationExecutor);
    }

    /**
     * VerifySpecificMaxLengthValidationSucceedsWithNoSetValue
     * @testDescription Verifies that the maxLength validation (isValidOnSpecifics) succeeds when no number has been set
     */
    @Test
    public void VerifySpecificMaxLengthValidationSucceedsWithNoSetValue()
    {
        TextInput textInput = createTextInputWithValidationProperties("", testMaxLength);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        Assert.assertTrue(textInputHandler.isValidOnSpecifics(""));
    }

    /**
     * VerifySpecificMaxLengthValidationSucceedsWithShortValues
     * @testDescription Verifies that the maxLength validation (isValidOnSpecifics) succeeds when a short value has been set
     */
    @Test
    public void VerifySpecificMaxLengthValidationSucceedsWithShortValues()
    {
        TextInput textInput = createTextInputWithValidationProperties("", testMaxLength);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.SpecificsValidationExecutor maxValidationExecutor = new TestUtil.SpecificsValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(c_shortStrings, true, maxValidationExecutor);
    }

    /**
     * VerifySpecificMaxLengthValidationFailsWithLongValues
     * @testDescription Verifies that the maxLength validation (isValidOnSpecifics) fails when a long value has been set
     */
    @Test
    public void VerifySpecificMaxLengthValidationFailsWithLongValues()
    {
        TextInput textInput = createTextInputWithValidationProperties("", testMaxLength);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.SpecificsValidationExecutor maxValidationExecutor = new TestUtil.SpecificsValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(c_longStrings, false, maxValidationExecutor);
    }

    /**
     * VerifyMaxLengthValidationSucceedsWithNoSetValue
     * @testDescription  Verifies that the maxLength validation (isValid) succeeds when no value has been set
     * and it's not required
     */
    @Test
    public void VerifyMaxLengthValidationSucceedsWithNoSetValue()
    {
        TextInput textInput = createTextInputWithValidationProperties("", testMaxLength);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        Assert.assertTrue(textInputHandler.isValid());
    }

    /**
     * VerifyMaxLengthValidationSucceedsWithShortValues
     * @testDescription Verifies that the maxLength validation (isValid) succeeds when a short value has been set
     */
    @Test
    public void VerifyMaxLengthValidationSucceedsWithShortValues()
    {
        TextInput textInput = createTextInputWithValidationProperties("", testMaxLength);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(c_shortStrings, true, validationExecutor);
    }

    /**
     * VerifyMaxLengthValidationSucceedsWithLongValues
     * @testDescription Verifies that the maxLength validation (isValid) fails when a large value has been set
     */
    @Test
    public void VerifyMaxLengthValidationSucceedsWithLongValues()
    {
        TextInput textInput = createTextInputWithValidationProperties("", testMaxLength);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(c_longStrings, false, validationExecutor);
    }

    /**
     * VerifyRequiredMaxLengthValidationFailsWithNoSetValue
     * @testDescription  Verifies that the maxLength and isRequired validation (isValid) fails when no value has been set
     */
    @Test
    public void VerifyRequiredMaxLengthValidationFailsWithNoSetValue()
    {
        TextInput textInput = createTextInputWithValidationProperties("", testMaxLength, true);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        Assert.assertFalse(textInputHandler.isValid());
    }

    /**
     * VerifyRequiredMaxLengthValidationSucceedsWithShortValues
     * @testDescription  Verifies that the maxLength and isRequired validation (isValid) succeeds when a short value has been set
     */
    @Test
    public void VerifyRequiredMaxLengthValidationSucceedsWithShortValues()
    {
        TextInput textInput = createTextInputWithValidationProperties("", testMaxLength, true);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(c_shortStrings, true, validationExecutor);
    }

    /**
     * VerifyRequiredMaxLengthValidationFailsWithLongValues
     * @testDescription  Verifies that the maxLength and isRequired validation (isValid) fail when a long value has been set
     */
    @Test
    public void VerifyRequiredMaxLengthValidationFailsWithLongValues()
    {
        TextInput textInput = createTextInputWithValidationProperties("", testMaxLength, true);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(c_longStrings, false, validationExecutor);
    }

    /**
     * VerifySpecificRegexMaxLengthValidationSucceedsWithNoSetValue
     * @testDescription Verifies that the regex and maxLength validation (isValidOnSpecifics) succeeds when no value has been set
     */
    @Test
    public void VerifySpecificRegexMaxLengthValidationSucceedsWithNoSetValue()
    {
        TextInput textInput = createTextInputWithValidationProperties("", testMaxLength);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        Assert.assertTrue(textInputHandler.isValidOnSpecifics(""));
    }

    /**
     * VerifySpecificRegexMaxLengthValidationFailsWithShortValues
     * @testDescription Verifies that the regex (with min length) and maxLength validation (isValidOnSpecifics)
     * fails when a short value has been set
     */
    @Test
    public void VerifySpecificRegexMaxLengthValidationFailsWithShortValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColorMinLength, testMaxLengthHexColor);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.SpecificsValidationExecutor regexMaxLengthValidationExecutor = new TestUtil.SpecificsValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(shortHexColors, false, regexMaxLengthValidationExecutor);
    }

    /**
     * VerifySpecificRegexMaxLengthValidationSucceedsWithValidValues
     * @testDescription Verifies that the regex and maxLength validation (isValidOnSpecifics) succeeds when a
     * value has been set and complies with the regex, the min length defined by the regex and is shorter than the maxLength
     */
    @Test
    public void VerifySpecificRegexMaxLengthValidationSucceedsWithValidValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColorMinLength, testMaxLengthHexColor);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.SpecificsValidationExecutor regexMaxLengthValidationExecutor = new TestUtil.SpecificsValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(validHexColors, true, regexMaxLengthValidationExecutor);
    }

    /**
     * VerifySpecificRegexMaxLengthValidationFailsWithLargeValues
     * @testDescription Verifies that the regex and maxLength validation (isValidOnSpecifics) fails when a long value has been set
     */
    @Test
    public void VerifySpecificRegexMaxLengthValidationFailsWithLargeValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColorMinLength, testMaxLengthHexColor);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.SpecificsValidationExecutor regexMaxLengthValidationExecutor = new TestUtil.SpecificsValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(longHexColors, false, regexMaxLengthValidationExecutor);
    }

    /**
     * VerifySpecificRegexMaxLengthValidationFailsWithInvalidValues
     * @testDescription Verifies that the regex and maxLength validation (isValidOnSpecifics) fails when an non
     * compliant value with the regex has been set
     */
    @Test
    public void VerifySpecificRegexMaxLengthValidationFailsWithInvalidValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColorMinLength, testMaxLengthHexColor);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.SpecificsValidationExecutor regexMaxLengthValidationExecutor = new TestUtil.SpecificsValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(invalidHexColors, false, regexMaxLengthValidationExecutor);
    }

    /**
     * VerifyRegexMaxLengthValidationSucceedsWithNoSetValue
     * @testDescription Verifies that the regex and maxLength validation (isValid) succeeds when no value has been set
     */
    @Test
    public void VerifyRegexMaxLengthValidationSucceedsWithNoSetValue()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColorMinLength, testMaxLengthHexColor);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        Assert.assertTrue(textInputHandler.isValid());
    }

    /**
     * VerifyRegexMaxLengthValidationFailsWithShortValues
     * @testDescription Verifies that the regex and maxLength validation (isValid) fails when a short value has been set
     */
    @Test
    public void VerifyRegexMaxLengthValidationFailsWithShortValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColorMinLength, testMaxLengthHexColor);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(shortHexColors, false, validationExecutor);
    }

    /**
     * VerifyRegexMaxLengthValidationSucceedsWithValidValues
     * @testDescription Verifies that the regex and maxLength validation (isValid) succeeds when a
     * value has been set and complies with the regex, the min length defined by the regex and is shorter than the maxLength
     */
    @Test
    public void VerifyRegexMaxLengthValidationSucceedsWithValidValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColorMinLength, testMaxLengthHexColor);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(validHexColors, true, validationExecutor);
    }

    /**
     * VerifyRegexMaxLengthValidationFailsWithLongValues
     * @testDescription Verifies that the regex and maxLength validation (isValid) fails when a long value has been set
     */
    @Test
    public void VerifyRegexMaxLengthValidationFailsWithLongValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColorMinLength, testMaxLengthHexColor);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(longHexColors, false, validationExecutor);
    }

    /**
     * VerifyRegexMaxLengthValidationFailsWithInvalidValues
     * @testDescription Verifies that the regex and maxLength validation (isValid) fails when an invalid value has been set
     */
    @Test
    public void VerifyRegexMaxLengthValidationFailsWithInvalidValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColorMinLength, testMaxLengthHexColor);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(invalidHexColors, false, validationExecutor);
    }

    /**
     * VerifyRequiredRegexMaxLengthValidationFailsWithNoSetValue
     * @testDescription Verifies that the isRequired, regex and maxLength validation (isValid) fails when no value has been set
     */
    @Test
    public void VerifyRequiredRegexMaxLengthValidationFailsWithNoSetValue()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColorMinLength, testMaxLengthHexColor, true);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        Assert.assertFalse(textInputHandler.isValid());
    }

    /**
     * VerifyRequiredRegexMaxLengthValidationFailsWithShortValues
     * @testDescription Verifies that the isRequired, regex and maxLength validation (isValid) fails when a short value has been set
     */
    @Test
    public void VerifyRequiredRegexMaxLengthValidationFailsWithShortValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColorMinLength, testMaxLengthHexColor, true);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(shortHexColors, false, validationExecutor);
    }

    /**
     * VerifyRequiredRegexMaxLengthValidationSucceedsWithValidValues
     * @testDescription Verifies that the isRequired, regex and maxLength validation (isValid) succeeds when a
     * value has been set and complies with the regex, the min length defined by the regex and is shorter than the maxLength
     */
    @Test
    public void VerifyRequiredRegexMaxLengthValidationSucceedsWithValidValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColorMinLength, testMaxLengthHexColor, true);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(validHexColors, true, validationExecutor);
    }

    /**
     * VerifyRequiredRegexMaxLengthValidationFailsWithLongValues
     * @testDescription Verifies that the isRequired, regex and maxLength validation (isValid) fails when a long value has been set
     */
    @Test
    public void VerifyRequiredRegexMaxLengthValidationFailsWithLongValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColorMinLength, testMaxLengthHexColor, true);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(longHexColors, false, validationExecutor);
    }

    /**
     * VerifyRequiredRegexMaxLengthValidationFailsWithInvalidValues
     * @testDescription Verifies that the isRequired, regex and maxLength validation (isValid) fails when an invalid value has been set
     */
    @Test
    public void VerifyRequiredRegexMaxLengthValidationFailsWithInvalidValues()
    {
        TextInput textInput = createTextInputWithValidationProperties(testRegexHexColorMinLength, testMaxLengthHexColor, true);
        TextInputHandler textInputHandler = createTextInputHandler(textInput);

        TestUtil.GeneralValidationExecutor validationExecutor = new TestUtil.GeneralValidationExecutor(textInputHandler);
        TestUtil.runValidationTests(invalidHexColors, false, validationExecutor);
    }

}
