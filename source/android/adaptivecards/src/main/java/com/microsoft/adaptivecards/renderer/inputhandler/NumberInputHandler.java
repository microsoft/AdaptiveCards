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
    }
}
