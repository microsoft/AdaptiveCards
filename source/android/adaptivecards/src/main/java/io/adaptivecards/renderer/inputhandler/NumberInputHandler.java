package io.adaptivecards.renderer.inputhandler;

import io.adaptivecards.objectmodel.BaseInputElement;

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
