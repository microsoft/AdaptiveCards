package io.adaptivecards.renderer.inputhandler.validation;

import android.widget.EditText;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class TextInputRegexValidator extends InputRegexValidator
{
    public TextInputRegexValidator(IInputValidator inputValidator) {
        super(inputValidator);
    }

    public TextInputRegexValidator(IInputValidator inputValidator, EditText editText, String regex)
    {
        super(inputValidator);
        m_editText = editText;
        m_regex = regex;
    }

    @Override
    public boolean fulfillsRegex()
    {
        return Pattern.matches(m_regex, m_editText.getText());
    }

    private EditText m_editText;
    private String m_regex;
}
