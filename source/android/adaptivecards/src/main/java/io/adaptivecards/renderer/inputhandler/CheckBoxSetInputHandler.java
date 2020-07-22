// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.inputhandler;

import android.text.Layout;
import android.text.TextUtils;
import android.widget.CheckBox;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.ChoiceInputVector;
import io.adaptivecards.objectmodel.ChoiceSetInput;

import java.util.Arrays;
import java.util.List;
import java.util.Vector;

public class CheckBoxSetInputHandler extends BaseInputHandler
{
    public CheckBoxSetInputHandler(BaseInputElement baseInputElement, List<CheckBox> checkBoxList)
    {
        super(baseInputElement);
        m_checkBoxList = checkBoxList;
    }

    protected List<CheckBox> getCheckBox() {
        return m_checkBoxList;
    }

    public String getInput()
    {
        // no need to validate
        ChoiceSetInput choiceSetInput = (ChoiceSetInput) m_baseInputElement;

        Vector<String> resultList = new Vector<String>();
        ChoiceInputVector choiceInputVector = choiceSetInput.GetChoices();
        for (int index = 0; index < m_checkBoxList.size(); index++)
        {
            if (m_checkBoxList.get(index).isChecked())
            {
                resultList.addElement(choiceInputVector.get(index).GetValue());
            }
        }

        return TextUtils.join(",", resultList);
    }

    public void setInput(String values)
    {
        ChoiceSetInput choiceSetInput = (ChoiceSetInput) m_baseInputElement;
        ChoiceInputVector choiceInputVector = choiceSetInput.GetChoices();

        if (values.isEmpty())
        {
            for (int i = 0 ; i < choiceInputVector.size(); i++)
            {
                m_checkBoxList.get(i).setChecked(false);
            }
            return;
        }

        List<String> listValues = Arrays.asList(values.split(";"));
        for (int i = 0 ; i < choiceInputVector.size(); i++)
        {
            if (listValues.contains(choiceInputVector.get(i).GetValue()))
            {
                m_checkBoxList.get(i).setChecked(true);
            }
            else
            {
                m_checkBoxList.get(i).setChecked(false);
            }
        }
    }

    @Override
    public void setFocusToView()
    {
        if (m_checkBoxList.size() > 0)
        {
            m_checkBoxList.get(0).setFocusableInTouchMode(true);
            m_checkBoxList.get(0).requestFocus();
        }
    }

    private List<CheckBox> m_checkBoxList;
}
