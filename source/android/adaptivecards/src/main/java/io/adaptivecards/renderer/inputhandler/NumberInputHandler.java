// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.inputhandler;

import android.widget.EditText;

import java.text.NumberFormat;
import java.util.regex.Pattern;

import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.NumberInput;
import io.adaptivecards.objectmodel.TextInput;

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
        NumberInput numberInput = null;
        if (m_baseInputElement instanceof TextInput)
        {
            numberInput = (NumberInput) m_baseInputElement;
        }
        else if ((numberInput = NumberInput.dynamic_cast(m_baseInputElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to NumberInput object model.");
        }

        int inputValue = 0;
        try
        {
            inputValue = Integer.parseInt(numberInputValue);
        }
        catch (Exception ex)
        {
            // Something failed, don't consider valid
            return false;
        }

        return (numberInput.GetMin() <= inputValue) && (inputValue <= numberInput.GetMax());
    }

}
