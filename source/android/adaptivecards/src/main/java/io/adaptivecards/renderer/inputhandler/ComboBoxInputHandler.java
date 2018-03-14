package io.adaptivecards.renderer.inputhandler;

import android.widget.Spinner;

import io.adaptivecards.objectmodel.BaseInputElement;
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
        return (String) getSpinner().getSelectedItem();
    }
}
