package com.microsoft.adaptivecards.renderer.inputhandler;

import android.widget.RadioGroup;

import com.microsoft.adaptivecards.objectmodel.BaseInputElement;
import com.microsoft.adaptivecards.objectmodel.ChoiceSetInput;

import java.text.ParseException;
import java.util.Map;

public class RadioGroupInputHandler extends BaseInputHandler
{
    public RadioGroupInputHandler(BaseInputElement baseInputElement)
    {
        super(baseInputElement);
    }

    protected RadioGroup getRadioGroup()
    {
        return (RadioGroup) m_view;
    }

    @Override
    protected void setDefaultTextColor()
    {
        //no op
    }

    @Override
    protected void setInvalidTextColor()
    {
        // no op
    }

    @Override
    protected void internalValidate()
            throws ParseException
    {
        // no need to validate
    }

    public Exception getData(Map<String, String> data)
    {
        // no need to validate
        ChoiceSetInput choiceSetInput = (ChoiceSetInput) m_baseInputElement;
        int index = getRadioGroup().getCheckedRadioButtonId();
        data.put(m_baseInputElement.GetId(), choiceSetInput.GetChoices().get(index).GetValue());
        return null;
    }

}
