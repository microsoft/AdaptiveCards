// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.inputhandler;

import android.widget.Spinner;

import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.ChoiceInput;
import io.adaptivecards.objectmodel.ChoiceInputVector;
import io.adaptivecards.objectmodel.ChoiceSetInput;

import java.text.ParseException;
import java.util.Map;

public class ComboBoxInputHandler extends BaseInputHandler
{
    public ComboBoxInputHandler(BaseInputElement baseInputElement)
    {
        super(baseInputElement);
    }

    protected Spinner getSpinner()
    {
        return (Spinner) m_view;
    }

    public String getInput()
    {
        // no need to validate
        ChoiceSetInput choiceSetInput = (ChoiceSetInput) m_baseInputElement;
        int index = getSpinner().getSelectedItemPosition();
        String selectedItem = "";
        if (index >= 0 && index < choiceSetInput.GetChoices().size())
        {
            selectedItem = choiceSetInput.GetChoices().get(index).GetValue();
        }
        return selectedItem;
    }

    public void setInput(String value)
    {
        ChoiceSetInput choiceSetInput = (ChoiceSetInput) m_baseInputElement;
        ChoiceInputVector choiceInputVector = choiceSetInput.GetChoices();
        int selectedPosition = 0;

        for (int i = 0; i < choiceInputVector.size(); i++)
        {
            ChoiceInput choiceInput = choiceInputVector.get(i);
            if (value.equals(choiceInput.GetValue()))
            {
                selectedPosition = i;
                break;
            }
        }

        getSpinner().setSelection(selectedPosition);
    }

    @Override
    public void setFocusToView()
    {
        m_view.requestFocus();
        m_view.performClick();
    }
}
