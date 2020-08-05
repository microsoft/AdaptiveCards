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

        int inputValue = 0;
        try
        {
            inputValue = Integer.parseInt(numberInputValue);
        }
        catch (Exception ex)
        {
            // Parsing failed, consider it invalid if it was not required otherwise it's invalid
            if (numberInputValue.isEmpty() && !numberInput.GetIsRequired())
            {
                return true;
            }
            else
            {
                return false;
            }
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
