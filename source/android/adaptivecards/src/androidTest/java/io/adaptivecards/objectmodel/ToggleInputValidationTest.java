package io.adaptivecards.objectmodel;

import android.support.test.InstrumentationRegistry;
import android.widget.CheckBox;
import android.widget.EditText;

import junit.framework.Assert;

import org.junit.Test;

import io.adaptivecards.renderer.inputhandler.TimeInputHandler;
import io.adaptivecards.renderer.inputhandler.ToggleInputHandler;

public class ToggleInputValidationTest
{
    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    private final String valueOn = "valid";
    private final String valueOff = "notValid";

    private ToggleInput createToggleInputWithValidationProperties(boolean isRequired)
    {
        ToggleInput toggleInput = TestUtil.createMockToggleInput();
        toggleInput.SetValueOn(valueOn);
        toggleInput.SetValueOff(valueOff);
        toggleInput.SetIsRequired(isRequired);
        return toggleInput;
    }

    private ToggleInputHandler createInputHandler(ToggleInput toggleInput)
    {
        ToggleInputHandler toggleInputHandler = new ToggleInputHandler(toggleInput);
        toggleInputHandler.setView(new CheckBox(InstrumentationRegistry.getContext()));
        return toggleInputHandler;
    }

    /**
     * VerifyValidationSucceedsWithNoSetValue
     * @testDescription Verifies that a not required input will succeed when no value has been set
     */
    @Test
    public void VerifyValidationSucceedsWithNoSetValue()
    {
        ToggleInput toggleInput = createToggleInputWithValidationProperties(false);
        ToggleInputHandler toggleInputHandler = createInputHandler(toggleInput);

        Assert.assertTrue(toggleInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationSucceedsWithSetValueOnValue
     * @testDescription Verifies that a not required input will succeed when the valueOn value has been set
     */
    @Test
    public void VerifyValidationSucceedsWithSetValueOnValue()
    {
        ToggleInput toggleInput = createToggleInputWithValidationProperties(false);
        ToggleInputHandler toggleInputHandler = createInputHandler(toggleInput);

        toggleInputHandler.setInput(valueOn);
        Assert.assertTrue(toggleInputHandler.isValid());
    }

    /**
     * VerifyValidationSucceedsWithSetValueOffValue
     * @testDescription Verifies that a not required input will succeed when the valueOff value has been set
     */
    @Test
    public void VerifyValidationSucceedsWithSetValueOffValue()
    {
        ToggleInput toggleInput = createToggleInputWithValidationProperties(false);
        ToggleInputHandler toggleInputHandler = createInputHandler(toggleInput);

        toggleInputHandler.setInput(valueOff);
        Assert.assertTrue(toggleInputHandler.isValid());
    }

    /**
     * VerifyValidationSucceedsWithSetInvalidValue
     * @testDescription Verifies that a not required input will succeed when a value that is neither valueOn or valueOff has been set
     */
    @Test
    public void VerifyValidationSucceedsWithSetInvalidValue()
    {
        ToggleInput toggleInput = createToggleInputWithValidationProperties(false);
        ToggleInputHandler toggleInputHandler = createInputHandler(toggleInput);

        toggleInputHandler.setInput("anotherString");
        Assert.assertTrue(toggleInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationFailsWithNoSetValue
     * @testDescription Verifies that a required input will fail when no value has been set
     */
    @Test
    public void VerifyIsRequiredValidationFailsWithNoSetValue()
    {
        ToggleInput toggleInput = createToggleInputWithValidationProperties(true);
        ToggleInputHandler toggleInputHandler = createInputHandler(toggleInput);

        Assert.assertFalse(toggleInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationFailsWithSetValueOffValue
     * @testDescription Verifies that a required input will fail when the valueOff value has been set
     */
    @Test
    public void VerifyIsRequiredValidationFailsWithSetValueOffValue()
    {
        ToggleInput toggleInput = createToggleInputWithValidationProperties(true);
        ToggleInputHandler toggleInputHandler = createInputHandler(toggleInput);

        toggleInputHandler.setInput(valueOff);
        Assert.assertFalse(toggleInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationSucceedsWithSetValueOnValue
     * @testDescription Verifies that a required input will succeed when the valueOn value has been set
     */
    @Test
    public void VerifyIsRequiredValidationSucceedsWithSetValueOnValue()
    {
        ToggleInput toggleInput = createToggleInputWithValidationProperties(true);
        ToggleInputHandler toggleInputHandler = createInputHandler(toggleInput);

        toggleInputHandler.setInput(valueOn);
        Assert.assertTrue(toggleInputHandler.isValid());
    }

    /**
     * VerifyIsRequiredValidationFailsWithSetInvalidValue
     * @testDescription Verifies that a required input will fail when a value that is neither valueOn or valueOff has been set
     */
    @Test
    public void VerifyIsRequiredValidationFailsWithSetInvalidValue()
    {
        ToggleInput toggleInput = createToggleInputWithValidationProperties(true);
        ToggleInputHandler toggleInputHandler = createInputHandler(toggleInput);

        toggleInputHandler.setInput("anotherString");
        Assert.assertFalse(toggleInputHandler.isValid());
    }
}
