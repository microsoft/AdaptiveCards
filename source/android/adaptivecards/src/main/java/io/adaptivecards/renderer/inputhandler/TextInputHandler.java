// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.inputhandler;

import android.widget.EditText;

import java.util.regex.Pattern;

import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.TextInput;
import io.adaptivecards.renderer.Util;

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

    public void setInput(String text)
    {
        getEditText().setText(text);
    }

    public String getInput()
    {
        return getEditText().getText().toString();
    }

    @Override
    public boolean isValidOnSpecifics(String textInputValue)
    {
        TextInput textInput = Util.tryCastTo(m_baseInputElement, TextInput.class);
        if (textInput == null)
        {
            return false;
        }

        boolean isValid = true;
        String regex = textInput.GetRegex();
        if (!regex.isEmpty())
        {
            isValid = Pattern.matches(regex, textInputValue);
        }

        long maxLength = textInput.GetMaxLength();
        if (maxLength != 0)
        {
            isValid &= (textInputValue.length() <= maxLength);
        }

        return isValid;
    }

    public void setFocusToView()
    {
        m_view.requestFocus();
    }
}
