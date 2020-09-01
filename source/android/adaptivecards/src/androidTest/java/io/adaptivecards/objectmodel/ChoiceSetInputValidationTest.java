package io.adaptivecards.objectmodel;

import android.support.test.InstrumentationRegistry;
import android.widget.ArrayAdapter;
import android.widget.CheckBox;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Spinner;

import junit.framework.Assert;

import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import io.adaptivecards.renderer.inputhandler.CheckBoxSetInputHandler;
import io.adaptivecards.renderer.inputhandler.ComboBoxInputHandler;
import io.adaptivecards.renderer.inputhandler.RadioGroupInputHandler;

public class ChoiceSetInputValidationTest
{
    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    private final String validValue = "sample value";
    private final String invalidValue = "an invalid value";

    private ChoiceSetInput createCompactChoiceSetInputWithValidationProperties(boolean isRequired)
    {
        ChoiceSetInput choiceSetInput = TestUtil.createMockChoiceSetInput();
        choiceSetInput.SetIsRequired(isRequired);
        return choiceSetInput;
    }

    private ChoiceSetInput createExpandedChoiceSetInputWithValidationProperties(boolean isRequired)
    {
        ChoiceSetInput choiceSetInput = TestUtil.createMockChoiceSetInput();
        choiceSetInput.SetChoiceSetStyle(ChoiceSetStyle.Expanded);
        choiceSetInput.SetIsRequired(isRequired);
        return choiceSetInput;
    }

    private ChoiceSetInput createMultiSelectChoiceSetInputWithValidationProperties(boolean isRequired)
    {
        ChoiceSetInput choiceSetInput = TestUtil.createMockChoiceSetInput();
        choiceSetInput.SetChoiceSetStyle(ChoiceSetStyle.Expanded);
        choiceSetInput.SetIsMultiSelect(true);
        choiceSetInput.SetIsRequired(isRequired);
        return choiceSetInput;
    }

    private ComboBoxInputHandler createComboBoxInputHandler(ChoiceSetInput choiceSetInput)
    {
        ComboBoxInputHandler choiceSetInputHandler = new ComboBoxInputHandler(choiceSetInput);
        Spinner spinner = new Spinner(InstrumentationRegistry.getContext());
        spinner.setAdapter(new ArrayAdapter<String>(InstrumentationRegistry.getContext(), android.R.layout.simple_spinner_item, new String[]{"sample title", ""}));
        spinner.setSelection(1);
        choiceSetInputHandler.setView(spinner);
        return choiceSetInputHandler;
    }

    private RadioGroupInputHandler createRadioGroupInputHandler(ChoiceSetInput choiceSetInput)
    {
        RadioGroupInputHandler choiceSetInputHandler = new RadioGroupInputHandler(choiceSetInput);

        RadioGroup radioGroup = new RadioGroup(InstrumentationRegistry.getContext());
        RadioButton radioButton = new RadioButton(InstrumentationRegistry.getContext());
        radioButton.setText("sample title");
        radioGroup.addView(radioButton);
        choiceSetInputHandler.setView(radioGroup);

        return  choiceSetInputHandler;
    }

    private CheckBoxSetInputHandler createCheckBoxSetInputHandler(ChoiceSetInput choiceSetInput)
    {
        List<CheckBox> checkBoxes = new ArrayList<>();
        CheckBox checkBox = new CheckBox(InstrumentationRegistry.getContext());
        checkBox.setText("sample title");
        checkBoxes.add(checkBox);

        CheckBoxSetInputHandler choiceSetInputHandler = new CheckBoxSetInputHandler(choiceSetInput, checkBoxes);
        choiceSetInputHandler.setView(new CheckBox(InstrumentationRegistry.getContext()));
        return choiceSetInputHandler;
    }

    /**
     * VerifyValidationSucceedsWithNoSetValueForCompactChoiceSet
     * @testDescription Verifies that a not required input will succeed when no value has been set
     */
    @Test
    public void VerifyValidationSucceedsWithNoSetValueForCompactChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createCompactChoiceSetInputWithValidationProperties(false);
        ComboBoxInputHandler comboBoxInputHandler = createComboBoxInputHandler(choiceSetInput);

        Assert.assertTrue(comboBoxInputHandler.isValid());
    }

    /**
     * VerifyValidationSucceedsWithSetValueForCompactChoiceSet
     * @testDescription Verifies that a not required input will succeed when a valid value has been set
     */
    @Test
    public void VerifyValidationSucceedsWithSetValueForCompactChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createCompactChoiceSetInputWithValidationProperties(false);
        ComboBoxInputHandler comboBoxInputHandler = createComboBoxInputHandler(choiceSetInput);

        comboBoxInputHandler.setInput(validValue);
        Assert.assertTrue(comboBoxInputHandler.isValid());
    }

    /**
     * VerifyValidationSucceedsWithSetInvalidValueForCompactChoiceSet
     * @testDescription Verifies that a not required input will succeed when a value not in the list of values has been set
     */
    @Test
    public void VerifyValidationSucceedsWithSetInvalidValueForCompactChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createCompactChoiceSetInputWithValidationProperties(false);
        ComboBoxInputHandler comboBoxInputHandler = createComboBoxInputHandler(choiceSetInput);

        comboBoxInputHandler.setInput(invalidValue);
        Assert.assertTrue(comboBoxInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationFailsWithNoSetValueForCompactChoiceSet
     * @testDescription Verifies that a required input will fail when no value has been set
     */
    @Test
    public void VerifyIsRequiredValidationFailsWithNoSetValueForCompactChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createCompactChoiceSetInputWithValidationProperties(true);
        ComboBoxInputHandler comboBoxInputHandler = createComboBoxInputHandler(choiceSetInput);

        Assert.assertFalse(comboBoxInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationSucceedsWithSetValueForCompactChoiceSet
     * @testDescription Verifies that a required input will succeed when a valid value has been set
     */
    @Test
    public void VerifyIsRequiredValidationSucceedsWithSetValueForCompactChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createCompactChoiceSetInputWithValidationProperties(true);
        ComboBoxInputHandler comboBoxInputHandler = createComboBoxInputHandler(choiceSetInput);

        comboBoxInputHandler.setInput(validValue);
        Assert.assertTrue(comboBoxInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationFailsWithSetInvalidValue
     * @testDescription Verifies that a required input will fail when a value not in the list of values has been set
     */
    @Test
    public void VerifyIsRequiredValidationFailsWithSetInvalidValueForCompactChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createCompactChoiceSetInputWithValidationProperties(true);
        ComboBoxInputHandler comboBoxInputHandler = createComboBoxInputHandler(choiceSetInput);

        comboBoxInputHandler.setInput(invalidValue);
        Assert.assertFalse(comboBoxInputHandler.isValid());
    }

    /**
     * VerifyValidationSucceedsWithNoSetValueForExpandedChoiceSet
     * @testDescription Verifies that a not required input will succeed when no value has been set
     */
    @Test
    public void VerifyValidationSucceedsWithNoSetValueForExpandedChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createExpandedChoiceSetInputWithValidationProperties(false);
        RadioGroupInputHandler radioGroupInputHandler = createRadioGroupInputHandler(choiceSetInput);

        Assert.assertTrue(radioGroupInputHandler.isValid());
    }

    /**
     * VerifyValidationSucceedsWithSetValueForExpandedChoiceSet
     * @testDescription Verifies that a not required input will succeed when a valid value has been set
     */
    @Test
    public void VerifyValidationSucceedsWithSetValueForExpandedChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createExpandedChoiceSetInputWithValidationProperties(false);
        RadioGroupInputHandler radioGroupInputHandler = createRadioGroupInputHandler(choiceSetInput);

        radioGroupInputHandler.setInput(validValue);
        Assert.assertTrue(radioGroupInputHandler.isValid());
    }

    /**
     * VerifyValidationSucceedsWithSetInvalidValueForExpandedChoiceSet
     * @testDescription Verifies that a not required input will succeed when a value not in the list of values has been set
     */
    @Test
    public void VerifyValidationSucceedsWithSetInvalidValueForExpandedChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createExpandedChoiceSetInputWithValidationProperties(false);
        RadioGroupInputHandler radioGroupInputHandler = createRadioGroupInputHandler(choiceSetInput);

        radioGroupInputHandler.setInput(invalidValue);
        Assert.assertTrue(radioGroupInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationFailsWithNoSetValueForExpandedChoiceSet
     * @testDescription Verifies that a required input will fail when no value has been set
     */
    @Test
    public void VerifyIsRequiredValidationFailsWithNoSetValueForExpandedChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createExpandedChoiceSetInputWithValidationProperties(true);
        RadioGroupInputHandler radioGroupInputHandler = createRadioGroupInputHandler(choiceSetInput);

        Assert.assertFalse(radioGroupInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationSucceedsWithSetValueForExpandedChoiceSet
     * @testDescription Verifies that a required input will succeed when a valid value has been set
     */
    @Test
    public void VerifyIsRequiredValidationSucceedsWithSetValueForExpandedChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createExpandedChoiceSetInputWithValidationProperties(true);
        RadioGroupInputHandler radioGroupInputHandler = createRadioGroupInputHandler(choiceSetInput);

        radioGroupInputHandler.setInput(validValue);
        Assert.assertTrue(radioGroupInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationFailsWithSetInvalidValueForExpandedChoiceSet
     * @testDescription Verifies that a required input will fail when a value not in the list of values has been set
     */
    @Test
    public void VerifyIsRequiredValidationFailsWithSetInvalidValueForExpandedChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createExpandedChoiceSetInputWithValidationProperties(true);
        RadioGroupInputHandler radioGroupInputHandler = createRadioGroupInputHandler(choiceSetInput);

        radioGroupInputHandler.setInput(invalidValue);
        Assert.assertFalse(radioGroupInputHandler.isValid());
    }

    /**
     * VerifyValidationSucceedsWithNoSetValueForMultiSelectChoiceSet
     * @testDescription Verifies that a not required input will succeed when no value has been set
     */
    @Test
    public void VerifyValidationSucceedsWithNoSetValueForMultiSelectChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createMultiSelectChoiceSetInputWithValidationProperties(false);
        CheckBoxSetInputHandler checkBoxSetInputHandler = createCheckBoxSetInputHandler(choiceSetInput);

        Assert.assertTrue(checkBoxSetInputHandler.isValid());
    }

    /**
     * VerifyValidationSucceedsWithSetValueForMultiSelectChoiceSet
     * @testDescription Verifies that a not required input will succeed when a valid value has been set
     */
    @Test
    public void VerifyValidationSucceedsWithSetValueForMultiSelectChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createMultiSelectChoiceSetInputWithValidationProperties(false);
        CheckBoxSetInputHandler checkBoxSetInputHandler = createCheckBoxSetInputHandler(choiceSetInput);

        checkBoxSetInputHandler.setInput(validValue);
        Assert.assertTrue(checkBoxSetInputHandler.isValid());
    }

    /**
     * VerifyValidationSucceedsWithSetInvalidValueForMultiSelectChoiceSet
     * @testDescription Verifies that a not required input will succeed when a value not in the list of values has been set
     */
    @Test
    public void VerifyValidationSucceedsWithSetInvalidValueForMultiSelectChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createMultiSelectChoiceSetInputWithValidationProperties(false);
        CheckBoxSetInputHandler checkBoxSetInputHandler = createCheckBoxSetInputHandler(choiceSetInput);

        checkBoxSetInputHandler.setInput(invalidValue);
        Assert.assertTrue(checkBoxSetInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationFailsWithNoSetValueForMultiSelectChoiceSet
     * @testDescription Verifies that a required input will fail when no value has been set
     */
    @Test
    public void VerifyIsRequiredValidationFailsWithNoSetValueForMultiSelectChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createMultiSelectChoiceSetInputWithValidationProperties(true);
        CheckBoxSetInputHandler checkBoxSetInputHandler = createCheckBoxSetInputHandler(choiceSetInput);

        Assert.assertFalse(checkBoxSetInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationSucceedsWithSetValueForMultiSelectChoiceSet
     * @testDescription Verifies that a required input will succeed when a valid value has been set
     */
    @Test
    public void VerifyIsRequiredValidationSucceedsWithSetValueForMultiSelectChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createMultiSelectChoiceSetInputWithValidationProperties(true);
        CheckBoxSetInputHandler checkBoxSetInputHandler = createCheckBoxSetInputHandler(choiceSetInput);

        checkBoxSetInputHandler.setInput(validValue);
        Assert.assertTrue(checkBoxSetInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationFailsWithSetInvalidValueForMultiSelectChoiceSet
     * @testDescription Verifies that a required input will fail when a value not in the list of values has been set
     */
    @Test
    public void VerifyIsRequiredValidationFailsWithSetInvalidValueForMultiSelectChoiceSet()
    {
        ChoiceSetInput choiceSetInput = createMultiSelectChoiceSetInputWithValidationProperties(true);
        CheckBoxSetInputHandler checkBoxSetInputHandler = createCheckBoxSetInputHandler(choiceSetInput);

        checkBoxSetInputHandler.setInput(invalidValue);
        Assert.assertFalse(checkBoxSetInputHandler.isValid());
    }













    @Test
    public void isRequiredMultiselectValidation()
    {
        ChoiceSetInput choiceSetInput = TestUtil.createMockChoiceSetInput();
        choiceSetInput.SetChoiceSetStyle(ChoiceSetStyle.Expanded);
        choiceSetInput.SetIsMultiSelect(true);
        choiceSetInput.SetIsRequired(true);

        List<CheckBox> checkBoxes = new ArrayList<>();
        CheckBox checkBox = new CheckBox(InstrumentationRegistry.getContext());
        checkBox.setText("sample title");
        checkBoxes.add(checkBox);

        CheckBoxSetInputHandler choiceSetInputHandler = new CheckBoxSetInputHandler(choiceSetInput, checkBoxes);
        choiceSetInputHandler.setView(new CheckBox(InstrumentationRegistry.getContext()));

        // Validate that empty input is always invalid
        Assert.assertEquals(false, choiceSetInputHandler.isValid());

        choiceSetInputHandler.setInput("sample value");
        Assert.assertEquals(true, choiceSetInputHandler.isValid());
    }

}
