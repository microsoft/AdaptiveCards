// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.inputhandler;

import android.widget.CheckBox;

import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.ToggleInput;

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
    public String getInput()
    {
        // no need to validate
        ToggleInput toggleInput = (ToggleInput) m_baseInputElement;
        CheckBox checkBox = getCheckBox();
        return checkBox.isChecked() ? toggleInput.GetValueOn() : toggleInput.GetValueOff();
    }

    public void setInput(String value)
    {
        ToggleInput toggleInput = (ToggleInput) m_baseInputElement;
        CheckBox checkBox = getCheckBox();
        checkBox.setChecked(value.equals(toggleInput.GetValueOn()));
    }

    @Override
    public boolean isValid()
    {
        boolean isValid = true;

        // Due to toggle not working as all other inputs where isRequired can be satisfied
        // with checking on empty values, we check on the state of the checkBox
        if (m_baseInputElement.GetIsRequired())
        {
            isValid = getCheckBox().isChecked();
        }

        showValidationErrors(isValid);

        return isValid;
    }

    @Override
    public void setFocusToView()
    {
        m_view.setFocusableInTouchMode(true);
        m_view.requestFocus();
    }
}
