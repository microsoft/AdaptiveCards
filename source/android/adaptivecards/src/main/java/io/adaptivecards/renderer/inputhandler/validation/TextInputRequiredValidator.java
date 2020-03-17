package io.adaptivecards.renderer.inputhandler.validation;

import android.widget.EditText;

public class TextInputRequiredValidator extends InputRequiredValidator
{
    public TextInputRequiredValidator(boolean isRequired) {
        super(isRequired);
    }

    public TextInputRequiredValidator(boolean isRequired, EditText editText)
    {
        super(isRequired);
        m_editText = editText;
    }

    @Override
    public boolean compliesRequired()
    {
        String text = m_editText.getText().toString();
        return !(text.trim().isEmpty());
    }

    private EditText m_editText;
}
