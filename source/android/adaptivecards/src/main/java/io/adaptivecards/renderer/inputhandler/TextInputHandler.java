// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.inputhandler;

import android.widget.EditText;

import java.util.regex.Pattern;

import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.TextInput;

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
        TextInput textInput = null;
        if (m_baseInputElement instanceof TextInput)
        {
            textInput = (TextInput) m_baseInputElement;
        }
        else if ((textInput = TextInput.dynamic_cast(m_baseInputElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to TextInput object model.");
        }

        boolean isValid = true;
        String regex = textInput.GetRegex();
        if (!regex.isEmpty())
        {
            isValid = Pattern.matches(regex, textInputValue);
        }

        return isValid;
    }

}
