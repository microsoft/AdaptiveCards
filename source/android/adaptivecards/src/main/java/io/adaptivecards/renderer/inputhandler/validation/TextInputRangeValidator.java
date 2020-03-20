package io.adaptivecards.renderer.inputhandler.validation;

import android.widget.EditText;

import java.util.regex.Pattern;

import io.adaptivecards.objectmodel.TextInput;

public abstract class TextInputRangeValidator extends ActualValidator
{
    public TextInputRangeValidator(IInputValidator inputValidator) {
        super(inputValidator);
    }

    public TextInputRangeValidator(IInputValidator inputValidator, Object min, Object max)
    {
        this(inputValidator);
        m_min = min;
        m_max = max;
    }

    @Override
    public boolean isValid()
    {
        String value = ((EditText)m_inputValidator.getViewsForValidation().get(0)).getText().toString();
        return isInRange(value, m_min, m_max) && m_inputValidator.isValid();
    }

    public abstract boolean isInRange(String value, Object min, Object max);

    private Object m_min;
    private Object m_max;
}
