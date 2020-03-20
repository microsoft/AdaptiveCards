package io.adaptivecards.renderer.inputhandler.validation;

import android.view.View;
import android.widget.EditText;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class TextInputValidator implements IInputValidator
{

    @Override
    public void setViewForValidation(View v) {
        m_textInput = (EditText)v;
    }

    @Override
    public List<View> getViewsForValidation() {
        return Arrays.asList(new View[]{m_textInput});
    }

    @Override
    public boolean isValid()
    {
        return true;
    }

    public EditText getTextInput()
    {
        return m_textInput;
    }

    protected EditText m_textInput;
}
