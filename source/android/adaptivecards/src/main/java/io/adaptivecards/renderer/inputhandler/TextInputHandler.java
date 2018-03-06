package io.adaptivecards.renderer.inputhandler;

import android.graphics.Color;
import android.widget.EditText;

import io.adaptivecards.objectmodel.BaseInputElement;

import java.text.ParseException;
import java.util.Map;

public class TextInputHandler extends BaseInputHandler
{
    public TextInputHandler(BaseInputElement baseInputElement)
    {
        super(baseInputElement);
    }

    protected EditText getEditText()
    {
        return (EditText) m_view;
    }

    public String getInput()
    {
        return getEditText().getText().toString();
    }
}
