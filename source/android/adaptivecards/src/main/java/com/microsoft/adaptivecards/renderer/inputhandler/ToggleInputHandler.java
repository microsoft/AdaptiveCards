package com.microsoft.adaptivecards.renderer.inputhandler;

import android.widget.CheckBox;

import com.microsoft.adaptivecards.objectmodel.BaseInputElement;
import com.microsoft.adaptivecards.objectmodel.ToggleInput;

import java.text.ParseException;
import java.util.Map;

public class ToggleInputHandler extends BaseInputHandler
{
    public ToggleInputHandler(BaseInputElement baseInputElement)
    {
        super(baseInputElement);
    }

    protected CheckBox getCheckBox()
    {
        return (CheckBox) m_view;
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
        ToggleInput toggleInput = (ToggleInput) m_baseInputElement;
        CheckBox checkBox = getCheckBox();
        data.put(m_baseInputElement.GetId(), checkBox.isChecked() ? toggleInput.GetValueOn() : toggleInput.GetValueOff());
        return null;
    }
}
