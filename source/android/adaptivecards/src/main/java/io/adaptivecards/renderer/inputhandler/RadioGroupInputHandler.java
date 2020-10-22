// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.inputhandler;

import android.view.accessibility.AccessibilityEvent;
import android.widget.RadioButton;
import android.widget.RadioGroup;

import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.ChoiceInput;
import io.adaptivecards.objectmodel.ChoiceInputVector;
import io.adaptivecards.objectmodel.ChoiceSetInput;

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

    public String getInput()
    {
        // no need to validate
        ChoiceSetInput choiceSetInput = (ChoiceSetInput) m_baseInputElement;
        int index = getRadioGroup().getCheckedRadioButtonId();

        // if no item was selected, index == -1, return empty string
        if (index >= 0)
        {
            return choiceSetInput.GetChoices().get(index).GetValue();
        }
        else
        {
            return "";
        }
    }

    public void setInput(String choice)
    {
        ChoiceSetInput choiceSetInput = (ChoiceSetInput) m_baseInputElement;
        RadioGroup radioGroup = getRadioGroup();
        ChoiceInputVector choiceInputVector = choiceSetInput.GetChoices();

        if (!choice.isEmpty())
        {
            for (int i = 0 ; i < choiceInputVector.size(); i++)
            {
                ChoiceInput choiceInput = choiceInputVector.get(i);
                if (choice.equals(choiceInput.GetValue()))
                {
                    /*
                        We can do this because the id is equal to the index . Check {@link ChoiceSetInputRender}
                     */
                    radioGroup.check(i);
                    break;
                }
            }
        }
        else
        {
            // Indicates no item was selected
            radioGroup.check(-1);
        }
    }

    @Override
    public void setFocusToView()
    {
        RadioGroup radioGroup = (RadioGroup)m_view;

        if (radioGroup.getChildCount() > 0)
        {
            RadioButton radioButton = (RadioButton)(radioGroup.getChildAt(0));

            radioButton.setFocusableInTouchMode(true);
            radioButton.requestFocus();
            radioButton.sendAccessibilityEvent(AccessibilityEvent.TYPE_VIEW_FOCUSED);
        }
    }

}
