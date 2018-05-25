package io.adaptivecards.renderer.inputhandler;

import android.widget.RadioGroup;

import io.adaptivecards.objectmodel.BaseInputElement;
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
        if (index >= 0) {
            return choiceSetInput.GetChoices().get(index).GetValue();
        }
        else {
            return "";
        }
    }

}
