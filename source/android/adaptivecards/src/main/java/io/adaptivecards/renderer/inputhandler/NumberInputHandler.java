// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.inputhandler;

import android.widget.EditText;

import java.text.NumberFormat;
import java.util.regex.Pattern;

import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.NumberInput;
import io.adaptivecards.objectmodel.TextInput;
import io.adaptivecards.renderer.Util;

public class NumberInputHandler extends TextInputHandler
{
    public NumberInputHandler(BaseInputElement baseInputElement)
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
    public boolean isValidOnSpecifics(String numberInputValue)
    {
        NumberInput numberInput = Util.tryCastTo(m_baseInputElement, NumberInput.class);
        if (numberInput == null)
        {
            return false;
        }

        // Before performing any validation, if the input value is empty and is not required, then it's valid
        if (numberInputValue.isEmpty() && !numberInput.GetIsRequired())
        {
            return true;
        }

        int inputValue = 0;
        try
        {
            inputValue = Integer.parseInt(numberInputValue);
        }
        catch (NumberFormatException ex)
        {
            // Parsing failed,  consider it invalid
            return false;
        }

        boolean isValid = true;
        if (numberInput.GetMin() != null)
        {
            isValid = (numberInput.GetMin() <= inputValue);
        }

        if (numberInput.GetMax() != null)
        {
            isValid = isValid && (inputValue <= numberInput.GetMax());
        }

        return isValid;
    }

}
