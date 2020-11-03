// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.inputhandler;

import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.input.customcontrols.IValidatedInputView;
import io.adaptivecards.renderer.input.customcontrols.ValidatedEditText;
import io.adaptivecards.renderer.input.customcontrols.ValidatedCheckBoxLayout;
import io.adaptivecards.renderer.layout.StretchableInputLayout;

public abstract class BaseInputHandler implements IInputHandler
{
    public BaseInputHandler(BaseInputElement baseInputElement)
    {
        m_baseInputElement = baseInputElement;
    }

    public void setView(View view)
    {
        m_view = view;
    }

    public View getView()
    {
        return m_view;
    }

    public BaseInputElement getBaseInputElement()
    {
        return m_baseInputElement;
    }

    public String getId()
    {
        return m_baseInputElement.GetId();
    }

    public void setInputLayout(StretchableInputLayout inputLayout)
    {
        m_inputLayout = inputLayout;
    }

    public boolean isValid()
    {
        boolean isValid = true;
        String inputValue = getInput();

        // This method validates that any field
        if (m_baseInputElement.GetIsRequired())
        {
            isValid = !(inputValue.isEmpty());
        }

        isValid = isValid && isValidOnSpecifics(inputValue);

        showValidationErrors(isValid);

        return isValid;
    }

    public boolean isValidOnSpecifics(String inputValue)
    {
        // By default return true as some inputs don't have any specific inputs (regex, min/max)
        return true;
    }

    public void showValidationErrors(boolean isValid)
    {
        // This must only be performed if there is an errorMessage, inputs rendered
        // without labels or error messages will have no inputLayout
        if (m_inputLayout != null)
        {
            m_inputLayout.setValidationResult(isValid);
        }
    }

    protected BaseInputElement m_baseInputElement = null;
    protected View m_view = null;
    private StretchableInputLayout m_inputLayout = null;

}
