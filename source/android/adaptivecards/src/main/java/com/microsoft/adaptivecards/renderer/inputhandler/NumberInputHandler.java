package com.microsoft.adaptivecards.renderer.inputhandler;

import com.microsoft.adaptivecards.objectmodel.BaseInputElement;
import com.microsoft.adaptivecards.objectmodel.NumberInput;

import java.text.ParseException;

public class NumberInputHandler extends TextInputHandler
{
    public NumberInputHandler(BaseInputElement baseInputElement)
    {
        super(baseInputElement);
    }

    @Override
    protected void internalValidate()
            throws ParseException
    {
        super.internalValidate();
        NumberInput numberInput = (NumberInput) m_baseInputElement;

        int value = Integer.parseInt(getEditText().getText().toString(), 10);
        if (value < numberInput.GetMin())
        {
            throw new IllegalArgumentException("Input, " + numberInput.GetId() + ", contains value, " + value + ", that is less than the minimum value, " + numberInput.GetMin() + ", allowed.");
        }

        if (value > numberInput.GetMax())
        {
            throw new IllegalArgumentException("Input, " + numberInput.GetId() + ", contains value, " + value + ", that is greater than the maximum value, " + numberInput.GetMax() + ", allowed.");
        }
    }
}
