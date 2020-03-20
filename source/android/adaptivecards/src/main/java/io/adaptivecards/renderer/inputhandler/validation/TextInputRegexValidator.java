package io.adaptivecards.renderer.inputhandler.validation;

import android.widget.EditText;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class TextInputRegexValidator extends ActualValidator
    {
    public TextInputRegexValidator(IInputValidator inputValidator)
    {
        super(inputValidator);
    }

    public TextInputRegexValidator(IInputValidator inputValidator, String regex)
    {
        this(inputValidator);
        m_regex = regex;
    }

    @Override
    public boolean isValid()
    {
        return fulfillsRegex() && m_inputValidator.isValid();
    }

    public boolean fulfillsRegex()
    {
        EditText editText = (EditText)m_inputValidator.getViewsForValidation().get(0);
        return Pattern.matches(m_regex, editText.getText());
    }

    private String m_regex;
}
