package io.adaptivecards.renderer.inputhandler.validation;

import android.widget.EditText;

public class TextInputRequiredValidator extends ActualValidator
{
    public TextInputRequiredValidator(IInputValidator inputValidator)
    {
        super(inputValidator);
    }

    @Override
    public boolean isValid()
    {
        return compliesRequired() && m_inputValidator.isValid();
    }

    public boolean compliesRequired()
    {
        EditText editText = (EditText)m_inputValidator.getViewsForValidation().get(0);
        String text = editText.getText().toString();
        return !(text.trim().isEmpty());
    }
}
